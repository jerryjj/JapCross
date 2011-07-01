#include "gameengine.h"

#include <QDebug>
#include <QStringList>
#include <QStringListIterator>

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
    //Dummy level definition
    int level_rows = 10;
    int level_cols = 10;

    QString tmp_lst = "0,11,22,33,44,55,66,77,88,99";

    QStringListIterator it(tmp_lst.split(","));
    while (it.hasNext())
        required_squares << it.next().toInt();
    qDebug() << required_squares;
    m_lvl_cols_left = required_squares.count();
    m_lvl_cols_over = 0;

    m_tbheaders.clear();
    for (int i=0; i<level_cols; ++i) {
        HeaderGroup *g = new HeaderGroup;
        g->insertItem(1);
        m_tbheaders.insert(i, g);
    }

    m_lrheaders.clear();
    for (int i=0; i<level_rows; ++i) {
        HeaderGroup *g = new HeaderGroup;
        g->insertItem(1);
        m_lrheaders.insert(i, g);
    }

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

    emit playableSquaresChanged();
    emit tbHeadersChanged();
    emit lrHeadersChanged();
}

void GameEngine::markPlayableSquare(int index)
{
    PlayableSquare *s = psquare(index);

    if (!s) return;

    if (!s->inUse()) {
        //qDebug() << "set square" << index << "active";
        s->setActive(true);
        s->setInUse(true);

        if (required_squares.contains(index)) {
            qDebug() << "found required cell at" << index;
            m_lvl_cols_left -= 1;
        } else {
            m_lvl_cols_over += 1;
        }
    } else {
        if (s->active()) {
            //qDebug() << "set square" << index << "inactive";
            s->setActive(false);

            if (required_squares.contains(index)) {
                qDebug() << "found required cell at" << index;
                m_lvl_cols_left += 1;
            } else {
                m_lvl_cols_over -= 1;
            }
        } else {
            //qDebug() << "set square" << index << "disabled";
            s->setActive(false);
            s->setInUse(false);
        }
    }

    qDebug() << "m_lvl_cols_left:" << m_lvl_cols_left;
    qDebug() << "m_lvl_cols_over:" << m_lvl_cols_over;
    if (m_lvl_cols_left == 0 && m_lvl_cols_over == 0)
        qDebug() << "level finished!";
}

void GameEngine::markTopColumnSquare(int col, int row)
{
    qDebug() << "markTopColumnSquare" << col << "," << row;
    NumberSquare *s = tbsquare(col, row);

    if (!s) return;

    if (s->inUse()) {
        s->setMarked(!s->marked());
    }
}

void GameEngine::markSideColumnSquare(int row, int col)
{
    qDebug() << "markSideColumnSquare" << row << "," << col;
    NumberSquare *s = lrsquare(row, col);

    if (!s) return;

    if (s->inUse()) {
        s->setMarked(!s->marked());
    }
}
