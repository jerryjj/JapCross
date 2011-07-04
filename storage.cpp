#include "storage.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QVariant>
#include <QDateTime>

#if defined(Q_WS_HARMATTAN)
#include <QDesktopServices>
#endif

#include <QDebug>

const int VERSION_MAJOR = 0;
const int VERSION_MINOR = 1;
const int VERSION_PATCH = 0;

Storage::Storage(QObject *parent) :
    QObject(parent),
    m_vmajor(0),
    m_vminor(0),
    m_vpatch(0),
    m_path("")
{
}

Storage::~Storage()
{
    if (m_db.isOpen()) m_db.close();
}

bool Storage::connect()
{
    // Find QSLite driver
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_path = m_adjustPath(m_path);
    m_path.append("mnonograms.db");

    //qDebug() << "DB path: " << m_path;
    m_db.setDatabaseName(m_path);

    // Open databasee
    return m_db.open();
}

void Storage::disconnect()
{
    if (m_db.isOpen()) m_db.close();
}

bool Storage::initialize()
{
    bool ret = true;

    // Create tables
    if (m_createVersionTable()) {
        m_createSavegameTable();

        // Check that tables exists
        if (m_db.tables().count() != 2) ret = false;
    } else {
        m_validateVersionTable();
    }

    return ret;
}

bool Storage::uninstall()
{
    m_db.close();

    QString path = "";
    path = m_adjustPath(path);
    path.append("mnonograms.db");

    return QFile::remove(path);
}

QSqlError Storage::lastError()
{
    return m_db.lastError();
}

// for Savegame
bool Storage::createSavegame(int grp, int lvl, int timespent, int cols_left, int cols_over, QStringList used, QStringList marked)
{
    //qDebug() << "createSavegame";
    if (! m_db.isOpen()) return false;

    bool ret = false;

    QDateTime now = QDateTime::currentDateTime();

    Savegame *m = new Savegame;
    m->created = now.toTime_t();
    m->updated = now.toTime_t();
    m->grp = grp;
    m->lvl = lvl;
    m->timespent = timespent;
    m->cols_left = cols_left;
    m->cols_over = cols_over;
    m->setUsedCells(used);
    m->setMarkedCells(marked);

    QSqlQuery q;
    ret = q.prepare("INSERT INTO sg (created, updated, grp, lvl, timespent, cleft, cover, cused, cmarked) "
        "VALUES (:created, :updated, :grp, :lvl, :timespent, :cleft, :cover, :cused, :cmarked)");

    if (ret) {
        q.bindValue(":created", m->created);
        q.bindValue(":updated", m->updated);
        q.bindValue(":grp", m->grp);
        q.bindValue(":lvl", m->lvl);
        q.bindValue(":timespent", m->timespent);
        q.bindValue(":cleft", m->cols_left);
        q.bindValue(":cover", m->cols_over);
        q.bindValue(":cused", m->cells_used);
        q.bindValue(":cmarked", m->cells_marked);

        ret = q.exec();
    }

    if (ret) m->id = q.lastInsertId().toInt();

    //qDebug() << "created with id" << m->id;

    return ret;
}

bool Storage::updateSavedgame(Savegame* m)
{
    //qDebug() << "updateSavedgame";

    if (! m_db.isOpen()) return false;

    bool ret = false;

    QDateTime now = QDateTime::currentDateTime();
    m->updated = now.toTime_t();

    QSqlQuery q;
    ret = q.prepare("UPDATE sg SET updated = :updated, timespent = :timespent, cleft = :cleft, cover = :cover, cused = :cused, cmarked = :cmarked WHERE id = :id");

    if (ret) {
        q.bindValue(":id", m->id);

        q.bindValue(":updated", m->updated);
        q.bindValue(":timespent", m->timespent);
        q.bindValue(":cleft", m->cols_left);
        q.bindValue(":cover", m->cols_over);
        q.bindValue(":cused", m->cells_used);
        q.bindValue(":cmarked", m->cells_marked);

        ret = q.exec();
    }

    return ret;

}

bool Storage::getSavedgame(int grp, int lvl, Savegame* m)
{
    //qDebug() << "getSavedgame" << grp << "," << lvl;
    if (! m_db.isOpen()) return false;

    QSqlQuery q(QString("SELECT id,created,updated,grp,lvl,timespent,cleft,cover,cused,cmarked FROM sg WHERE grp = %1 AND lvl = %2").arg(grp).arg(lvl));

    if (q.next()) {
        m->id = q.value(0).toInt();
        m->created = q.value(1).toInt();
        m->updated = q.value(2).toInt();
        m->grp = q.value(3).toInt();
        m->lvl = q.value(4).toInt();
        m->timespent = q.value(5).toInt();
        m->cols_left = q.value(6).toInt();
        m->cols_over = q.value(7).toInt();
        m->cells_used = q.value(8).toString();
        m->cells_marked = q.value(9).toString();

        return true;
    }

    return false;
}

bool Storage::deleteSavegame(int grp, int lvl)
{
    if (! m_db.isOpen()) return false;
    bool ret = false;

    QSqlQuery query(QString("SELECT id FROM sg WHERE grp = %1 AND lvl = %2").arg(grp).arg(lvl));
    if (query.next()) {
        QSqlQuery q;
        if (q.prepare("DELETE FROM sg WHERE id = :id")) {
            q.bindValue(":id", query.value(0).toInt());
            ret = q.exec();
        }

        return ret;
    }

    return false;
}

bool Storage::m_createVersionTable()
{
    if (! m_db.isOpen()) return false;
    bool ret = false;
    QSqlQuery query;
    ret = query.exec("CREATE TABLE mnv (vmajor integer, vminor integer, vpatch integer)");

    if (ret) {
        QSqlQuery q;
        bool qr = q.prepare("INSERT INTO mnv (vmajor, vminor, vpatch) "
            "VALUES (:major, :minor, :patch)");

        if (qr) {
            q.bindValue(":major", QVariant(VERSION_MAJOR));
            q.bindValue(":minor", QVariant(VERSION_MINOR));
            q.bindValue(":patch", QVariant(VERSION_PATCH));
            ret = q.exec();
        }
    }

    return ret;
}

void Storage::m_validateVersionTable()
{
    if (! m_db.isOpen()) return;

    QSqlQuery query(QString("SELECT vmajor,vminor,vpatch FROM mnv WHERE rowid = 1"));
    if (query.next()) {
        m_vmajor = query.value(0).toInt();
        m_vminor = query.value(1).toInt();
        m_vpatch = query.value(2).toInt();
    }

    if (m_vmajor > VERSION_MAJOR) {
        //Downgrade. What to do here?
    }
    else if (VERSION_MAJOR > m_vmajor || VERSION_MINOR > m_vminor || VERSION_PATCH > m_vpatch) {
        QSqlQuery q;
        bool qp = q.prepare("UPDATE mnv SET vmajor = :major, vminor = :minor, vpatch = :patch WHERE rowid = 1");

        if (qp) {
            q.bindValue(":major", VERSION_MAJOR);
            q.bindValue(":minor", VERSION_MINOR);
            q.bindValue(":patch", VERSION_PATCH);
            q.exec();
        }
    }
}

bool Storage::m_createSavegameTable()
{
    if (! m_db.isOpen()) return false;
    bool ret = false;
    QSqlQuery query;

    ret = query.exec("CREATE TABLE sg "
                     "(id integer primary key, "
                     "created integer, "
                     "updated integer, "
                     "grp integer, "
                     "lvl integer, "
                     "timespent integer, "
                     "cleft integer, "
                     "cover integer, "
                     "cused text, "
                     "cmarked text)");

    return ret;
}

QString Storage::m_adjustPath(const QString &path)
{
#if defined(Q_WS_HARMATTAN)
    QString p = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + QLatin1Char('/') + path;
    p = QDir::toNativeSeparators(p.replace("//", "/"));

    if (!QFileInfo(p).exists()) {
        QDir().mkdir(p);
    }

    return p;
#else

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
        return QDir::toNativeSeparators(pathInShareDir);
#endif
    return QDir::toNativeSeparators(path);

#endif //defined(Q_WS_HARMATTAN)
}
