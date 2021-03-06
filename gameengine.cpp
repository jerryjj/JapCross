#include "gameengine.h"
#include "levelengine.h"
#include "statemachine.h"

#include "dbmodels.h"

#include <QDebug>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    connect(&m_active_level, SIGNAL(prepared()), this, SLOT(levelPrepared()));
    connect(&m_active_level, SIGNAL(finished()), this, SLOT(levelDone()));
}

GameEngine::~GameEngine()
{
}

void GameEngine::setStorage(Storage *str)
{
    m_storage = str;
}

void GameEngine::loadLevel(int grp, int idx)
{
    //qDebug() << "loadLevel" << grp << "," << idx;

    m_requested_level_available = false;
    stateMachine().setGameUIVisible(false);
    stateMachine().setGameInProgress(false);

    if (levelEngine().hasLevel(grp, idx)) {
        m_requested_level_available = true;
        //m_has_stored_game = false;
        stateMachine().setLoadingLevel(true);
        levelEngine().loadLevelByGroup(grp, idx);
    }
}

void GameEngine::startLevelLoad()
{
    emit levelLoading();

    if (m_requested_level_available) {
        levelEngine().startLoad(m_active_level);
        m_active_level.prepare();
    }
}

void GameEngine::levelPrepared()
{
    //qDebug() << "level prepared";

    emit levelChanged();
    emit levelReady();

    stateMachine().setLoadingLevel(false);
    stateMachine().setGameUIVisible(true);
}

void GameEngine::levelDone()
{
    //qDebug() << "level done";

    if (m_storage->isNewHighscore(m_active_level.grp, m_active_level.lvl, m_active_level.timespent())) {
        m_storage->updateHighscore(m_active_level.grp, m_active_level.lvl, m_active_level.timespent());
    }

    emit levelFinished();
}

void GameEngine::markPlayableCell(int index)
{
    //qDebug() << "GameEngine::markPlayableSquare" << index;

    m_active_level.markPlayableCell(index);
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

void GameEngine::pauseGame()
{
    if (!stateMachine().gameUIVisible()) {
        return;
    }

    if (! m_active_level.levelFinished()) {
        m_active_level.pauseLevel();
        saveGameState();
    }
}

void GameEngine::continueGame()
{
    if (!stateMachine().gameUIVisible()) {
        return;
    }

    if (! m_active_level.levelFinished()) {
        m_active_level.continueLevel();
    }
}

void GameEngine::saveGameState()
{
    if (!stateMachine().gameUIVisible()) {
        return;
    }

    Savegame m;

    if (!m_storage->getSavedgame(m_active_level.grp, m_active_level.lvl, &m)) {
        m_storage->createSavegame(m_active_level.grp, m_active_level.lvl, m_active_level.timespent(), m_active_level.colsLeft(), m_active_level.colsOver(), m_active_level.usedCells(), m_active_level.markedCells());
    } else {
        m.timespent = m_active_level.timespent();
        m.cols_left = m_active_level.colsLeft();
        m.cols_over = m_active_level.colsOver();
        m.setUsedCells(m_active_level.usedCells());
        m.setMarkedCells(m_active_level.markedCells());

        m_storage->updateSavedgame(&m);
    }

    levelEngine().updateLevelModelCacheItem(&m_active_level);
}

void GameEngine::clearGameState()
{
    //qDebug() << "clearGameState";

    Savegame m;

    if (m_storage->getSavedgame(m_active_level.grp, m_active_level.lvl, &m)) {
        m_storage->deleteSavegame(m_active_level.grp, m_active_level.lvl);
    }

    loadLevel(m_active_level.grp, m_active_level.lvl);
}
