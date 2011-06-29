#include "gameengine.h"

#include <QDebug>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    m_prepareColumns();
}

GameEngine::~GameEngine()
{
}

/*void GameEngine::setStorage(Storage *str)
{
    m_storage = str;
}
*/

void GameEngine::m_prepareColumns()
{
    //TODO: Get these from level info
    int level_rows = 10;
    int level_cols = 10;

    if (m_playableSquares.size() <= 0) {
        for (int i=0; i<level_rows*level_cols; ++i) {
            PlayableSquare *s = new PlayableSquare;
            m_playableSquares << s;
        }
    } else {
        for (int i=0; i<level_rows*level_cols; ++i) {
            m_playableSquares.at(i)->setActive(false);
            m_playableSquares.at(i)->setInUse(false);
        }
    }

    if (m_topColumns.size() <= 0) {
        for (int i=0; i<level_rows*level_cols; ++i) {
            NumberSquare *s = new NumberSquare;
            m_topColumns << s;
        }
    } else {
        for (int i=0; i<level_rows*level_cols; ++i) {
            m_topColumns.at(i)->setMarked(false);
            m_topColumns.at(i)->setInUse(false);
        }
    }

    if (m_sideColumns.size() <= 0) {
        for (int i=0; i<level_rows*level_cols; ++i) {
            NumberSquare *s = new NumberSquare;
            m_sideColumns << s;
        }
    } else {
        for (int i=0; i<level_rows*level_cols; ++i) {
            m_sideColumns.at(i)->setMarked(false);
            m_sideColumns.at(i)->setInUse(false);
        }
    }

    m_topColumns.at(0)->setInUse(true);
    m_topColumns.at(0)->setValue(1);

    m_sideColumns.at(0)->setInUse(true);
    m_sideColumns.at(0)->setValue(1);

    emit playableSquaresChanged();
    emit topColumnsChanged();
    emit sideColumnsChanged();
}

void GameEngine::markPlayableSquare(int index)
{
    PlayableSquare *s = psquare(index);

    if (!s) return;

    if (!s->inUse()) {
        //qDebug() << "set square" << index << "active";
        s->setActive(true);
        s->setInUse(true);
    } else {
        if (s->active()) {
            //qDebug() << "set square" << index << "inactive";
            s->setActive(false);
        } else {
            //qDebug() << "set square" << index << "disabled";
            s->setActive(false);
            s->setInUse(false);
        }
    }
}

void GameEngine::markTopColumnSquare(int index)
{
    NumberSquare *s = tnsquare(index);

    if (!s) return;

    if (s->inUse()) {
        s->setMarked(!s->marked());
    }
}

void GameEngine::markSideColumnSquare(int index)
{
    NumberSquare *s = snsquare(index);

    if (!s) return;

    if (s->inUse()) {
        s->setMarked(!s->marked());
    }
}
