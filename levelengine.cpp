#include "levelengine.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QDirIterator>

class LevelEnginePrivate
{
    QString levelsPath;
    friend class LevelEngine;
    static QString adjustPath(const QString &path);
};

QString LevelEnginePrivate::adjustPath(const QString &path)
{
#if defined(Q_OS_UNIX) || defined(Q_OS_MAC)
    if (!QDir::isAbsolutePath(path))
        return QCoreApplication::applicationDirPath()
                + QLatin1String("/../Resources/") + path;
#else
    const QString pathInShareDir = QCoreApplication::applicationDirPath()
        + QLatin1String("/../share/")
        + QFileInfo(QCoreApplication::applicationFilePath()).fileName()
        + QLatin1Char('/') + path;
    if (QFileInfo(pathInShareDir).exists())
        return pathInShareDir;
#endif
    return path;
}

LevelEngine::LevelEngine(QObject *parent) :
    QObject(parent),
    m_active_group(0),
    m_active_group_name(""),
    m_active_level(-1),
    m_active_level_name(""),
    m_lep(new LevelEnginePrivate)
{
}

LevelEngine::~LevelEngine()
{
    delete m_lep;
}

//void LevelEngine::setStorage(Storage *str)
//{
//    m_storage = str;
//}

void LevelEngine::setLevelsPath(const QString &path)
{
    m_lep->levelsPath = LevelEnginePrivate::adjustPath(path);
    //qDebug() << "m_lep->levelsPath" << m_lep->levelsPath;
}

void LevelEngine::collectLevels()
{
    QFileInfo fi;
    QDirIterator it(":/levels", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        fi = it.fileInfo();
        if (! fi.isFile()) continue;

        int grp = m_addGroup(fi.absolutePath().split("/").last());
        m_cacheLevelPath(grp, fi.filePath());
    }

    if (QFileInfo(m_lep->levelsPath).exists()) {
        QDirIterator lit(m_lep->levelsPath, QDirIterator::Subdirectories);
        while (lit.hasNext()) {
            lit.next();
            fi = lit.fileInfo();
            if (! fi.isFile()) continue;

            int grp = m_addGroup(fi.absolutePath().split("/").last());
            m_cacheLevelPath(grp, fi.filePath());
        }
    }

    emit levelsLoaded();
}

bool LevelEngine::hasLevel(int grp, int idx)
{
    if (m_levelsByGroup.size() < grp) return false;

    levelPathList lpl = m_levelsByGroup.value(grp);
    if (lpl.size() < idx) return false;

    return true;
}

void LevelEngine::loadLevelByGroup(int grp, int idx)//, Level &lvl)
{
    m_active_group = grp;
    m_active_level = idx;
    //m_loadLevelByGroup(m_active_group, m_active_level, lvl);
}

void LevelEngine::startLoad(Level &lvl)
{
    m_loadLevelByGroup(m_active_group, m_active_level, lvl);
}

int LevelEngine::m_addGroup(QString grp)
{
    if (! m_groups.contains(grp)) m_groups.append(grp);
    return m_groups.indexOf(grp);
}

void LevelEngine::m_cacheLevelPath(int grp, QString path)
{
    if (m_levelsByGroup.contains(grp)) {
        levelPathList lpl = m_levelsByGroup.value(grp);
        lpl << path;
        m_levelsByGroup.insert(grp, lpl);
    } else {
        levelPathList lpl;
        lpl << path;
        m_levelsByGroup.insert(grp, lpl);
    }

    levelPathList lpl = m_levelsByGroup.value(grp);

    LevelModel *lm = new LevelModel;

    int lvl = lpl.indexOf(path);

    QString grpName = m_groups.at(grp);
    grpName = grpName.replace("_", " ");
    grpName = grpName.replace(0, 1, grpName.at(0).toUpper());
    QString lvlName;
    int rows;
    int cols;
    m_readLevelData(path, lvlName, rows, cols);

    lm->setGrp(grp);
    lm->setGrpName(grpName);
    lm->setLvl(lvl);
    lm->setLvlName(lvlName);
    lm->setRows(rows);
    lm->setCols(cols);

    /*
    if (m_storage->hasLevelHighscore(grp, lvl)) {
        Highscore hs;
        bool s = m_storage->getLevelHighscore(grp, lvl, &hs);
        if (s) {
            lm->setHasHighscore(true);
            lm->setScore(hs.score);
            lm->setPercentage(hs.percentage);
            //m_storage->updateGameLevelHS(grp, lvl, hs.score, hs.percentage);
        }
        lm->setPlayable(true);
    }
    */

    m_lvl_models << lm;

    emit availableLevelsChanged();
}

void LevelEngine::m_loadLevelByGroup(int grp, int idx, Level &lvl)
{
    if (! m_levelsByGroup.contains(grp)) {
        //TODO: raise LEVEL_GROUP_NOT_FOUND
    }

    levelPathList lpl = m_levelsByGroup.value(grp);

    //TODO: Check if exists, raise if necessary
    QString path = lpl.at(idx);

    m_loadLevel(path, lvl);
}

void LevelEngine::m_loadLevel(QString path, Level &lvl)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QDataStream stream(&file);

    quint32 chk;
    stream >> chk;
    if (chk != 0xA0B0C0D0)
        return;// TODO: Raise exception BAD_FILE_FORMAT

    // Read the version
    qint32 version;
    stream >> version;

    if (version < 100)
        return;//TODO: Raise exception BAD_FILE_TOO_OLD
    if (version > 100)
        return;//TODO: Raise exception BAD_FILE_TOO_NEW
    if (version == 100)
        stream.setVersion(QDataStream::Qt_4_7);

    stream >> lvl;

    m_active_group_name = m_groups.at(m_active_group);
    m_active_group_name = m_active_group_name.replace("_", " ");
    m_active_group_name = m_active_group_name.replace(0, 1, m_active_group_name.at(0).toUpper());
    m_active_level_name = lvl.name();
}

void LevelEngine::m_readLevelData(QString path, QString &name, int &rows, int &cols)
{
    Level lvl;

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QDataStream stream(&file);

    quint32 chk;
    stream >> chk;
    if (chk != 0xA0B0C0D0)
        return;// TODO: Raise exception BAD_FILE_FORMAT

    // Read the version
    qint32 version;
    stream >> version;

    if (version < 100)
        return;//TODO: Raise exception BAD_FILE_TOO_OLD
    if (version > 100)
        return;//TODO: Raise exception BAD_FILE_TOO_NEW
    if (version == 100)
        stream.setVersion(QDataStream::Qt_4_7);

    stream >> lvl;

    name = lvl.name();
    rows = lvl.rows();
    cols = lvl.cols();
}

LevelEngine& levelEngine() {
    static LevelEngine le;
    return le;
};
