#include "dbmodels.h"

Savegame::Savegame()
{
    id = 0;
    created = 0;
    updated = 0;
    grp = 0;
    lvl = 0;
    timespent = 0;
    cols_left = 0;
    cols_over = 0;
    cells_used = "";
    cells_marked = "";
}

void Savegame::setUsedCells(QStringList cells)
{
    cells_used = cells.join(",");
}

QStringList Savegame::getUsedCells()
{
    QStringList s;
    if (cells_used == "") return s;
    return cells_used.split(",");
}

void Savegame::setMarkedCells(QStringList cells)
{
    cells_marked = cells.join(",");
}

QStringList Savegame::getMarkedCells()
{
    QStringList s;
    if (cells_marked == "") return s;
    return cells_marked.split(",");
}

Highscore::Highscore()
{
    created = 0;

    grp = 0;
    lvl = 0;
    timespent = 0;
}
