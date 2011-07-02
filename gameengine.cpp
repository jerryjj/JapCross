#include "gameengine.h"

#include <QDebug>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    m_active_level = new Level;

    connect(m_active_level, SIGNAL(prepared()), this, SLOT(levelPrepared()));
    connect(m_active_level, SIGNAL(finished()), this, SLOT(levelDone()));
}

GameEngine::~GameEngine()
{
}

/*void GameEngine::setStorage(Storage *str)
{
    m_storage = str;
}
*/

void GameEngine::loadLevel(int idx)
{
    qDebug() << "loadLevel" << idx;

    // Dummy level loading
    m_active_level->setLevelData(10, 10, QString("0,9,11,18,22,27,33,36,44,45,55,54,66,63,77,72,88,81,99,90")); // "0,11,22,33,44,55,66,77,88,99"
}

void GameEngine::levelPrepared()
{
    qDebug() << "level prepared";
    emit levelChanged();
    emit levelReady();
}

void GameEngine::levelDone()
{
    qDebug() << "level done";
    emit levelFinished();
}

void GameEngine::markPlayableCell(int index)
{
    //TODO: do point collection here
    //qDebug() << "GameEngine::markPlayableSquare" << index;

    m_active_level->markPlayableCell(index);
}

void GameEngine::markTopColumnSquare(int col, int row)
{
    //qDebug() << "markTopColumnSquare" << col << "," << row;
    NumberSquare *s = tbsquare(col, row);

    if (!s) return;

    if (s->inUse()) {
        s->setMarked(!s->marked());
    }
}

void GameEngine::markSideColumnSquare(int row, int col)
{
    //qDebug() << "markSideColumnSquare" << row << "," << col;
    NumberSquare *s = lrsquare(row, col);

    if (!s) return;

    if (s->inUse()) {
        s->setMarked(!s->marked());
    }
}
