#ifndef LEVELENGINE_H
#define LEVELENGINE_H

#include <QObject>

#include "level.h"
#include "levelmodel.h"

typedef QStringList groupList;
typedef QStringList levelPathList;
typedef QMap<int, levelPathList> levelPathMap;

class LevelEngine : public QObject
{
    Q_OBJECT
public:
    explicit LevelEngine(QObject *parent = 0);
    virtual ~LevelEngine();

    //void setStorage(Storage *str);
    void setLevelsPath(const QString &path);

    Q_PROPERTY(int activeGroup READ activeGroup);
    int activeGroup() const { return m_active_group; }

    Q_PROPERTY(int activeLevel READ activeLevel);
    int activeLevel() const { return m_active_level; }

    Q_PROPERTY(QString activeGroupName READ activeGroupName);
    QString activeGroupName() const { return m_active_group_name; }

    Q_PROPERTY(QString activeLevelName READ activeLevelName);
    QString activeLevelName() const { return m_active_level_name; }

    Q_PROPERTY(QDeclarativeListProperty<LevelModel> availableLevels READ availableLevels NOTIFY availableLevelsChanged);
    QDeclarativeListProperty<LevelModel> availableLevels() { return QDeclarativeListProperty<LevelModel>(this, m_lvl_models); }

    bool hasLevel(int grp, int idx);
    void loadLevelByGroup(int grp, int idx);//, Level &lvl);
    void startLoad(Level &lvl);

signals:
    void levelsLoaded();
    void availableLevelsChanged();

public slots:
    void collectLevels();

private:
    //Storage* m_storage;

    int m_addGroup(QString grp);
    void m_cacheLevelPath(int grp, QString path);
    void m_loadLevelByGroup(int grp, int idx, Level &lvl);
    void m_loadLevel(QString path, Level &lvl);
    void m_readLevelData(QString path, QString &name, QString &author, int &rows, int &cols);

    int m_active_group;
    QString m_active_group_name;
    int m_active_level;
    QString m_active_level_name;
    groupList m_groups;
    levelPathMap m_levelsByGroup;

    QList<LevelModel *> m_lvl_models;

    class LevelEnginePrivate *m_lep;

    LevelEngine(const LevelEngine&);
    friend LevelEngine& levelEngine();

};

LevelEngine& levelEngine();

#endif // LEVELENGINE_H
