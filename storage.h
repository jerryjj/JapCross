#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QStringList>

#include "dbmodels.h"

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);
    ~Storage();

    bool connect();
    bool initialize();
    bool uninstall();

    void disconnect();

    QSqlError lastError();

    // for Savegame
    bool createSavegame(int grp, int lvl, int timespent, int cols_left, int cols_over, QStringList used, QStringList marked);
    bool updateSavedgame(Savegame* m);
    bool getSavedgame(int grp, int lvl, Savegame* m);
    bool deleteSavegame(int grp, int lvl);

private:
    int m_vmajor;
    int m_vminor;
    int m_vpatch;

    bool m_createVersionTable();
    void m_validateVersionTable();
    bool m_createSavegameTable();

    QString m_path;
    QString m_adjustPath(const QString &path);

    QSqlDatabase m_db;
};

#endif // STORAGE_H
