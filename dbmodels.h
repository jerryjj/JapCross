#ifndef DBMODELS_H
#define DBMODELS_H

#include <QStringList>

class Savegame // Savegame model
{
public:
    Savegame();

    int id;
    int created;
    int updated;

    int grp;
    int lvl;
    int timespent;
    int cols_left;
    int cols_over;

    QString cells_used;
    QString cells_marked;

    void setUsedCells(QStringList cells);
    QStringList getUsedCells();

    void setMarkedCells(QStringList cells);
    QStringList getMarkedCells();
};

class Highscore // Highscore model
{
public:
    Highscore();

    int created;

    int grp;
    int lvl;
    int timespent;
};

#endif // DBMODELS_H
