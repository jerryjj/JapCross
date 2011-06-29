#include "gameengine.h"

#include <QDebug>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    m_preparePlayableSquares();
}

GameEngine::~GameEngine()
{
}

/*void GameEngine::setStorage(Storage *str)
{
    m_storage = str;
}
*/

void GameEngine::m_preparePlayableSquares()
{
    //TODO: Get these from level info
    int level_rows = 10;
    int level_cols = 10;

    if (m_playableSquares.size() <= 0) {
        for (int i=0; i<level_rows*level_cols; ++i) {
            PlayableSquare *ps = new PlayableSquare;
            m_playableSquares << ps;
        }
    } else {
        for (int i=0; i<level_rows*level_cols; ++i) {
            m_playableSquares.at(i)->setActive(false);
            m_playableSquares.at(i)->setInUse(false);
        }
    }
}

void GameEngine::markPlayableSquare(int index)
{
    PlayableSquare *ps = psquare(index);

    if (!ps)
        return;

    if (!ps->inUse()) {
        qDebug() << "set square" << index << "active";
        ps->setActive(true);
        ps->setInUse(true);
    } else {
        if (ps->active()) {
            qDebug() << "set square" << index << "inactive";
            ps->setActive(false);
        } else {
            qDebug() << "set square" << index << "disabled";
            ps->setActive(false);
            ps->setInUse(false);
        }
    }
}
