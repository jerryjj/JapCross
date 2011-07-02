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

    //QString tmp_lst = "0,11,22,33,44,55,66,77,88,99";
    QString tmp_lst = "0,9,11,18,22,27,33,36,44,45,55,54,66,63,77,72,88,81,99,90";

    QStringListIterator it(tmp_lst.split(","));
    while (it.hasNext())
        required_squares << it.next().toInt();
    qDebug() << required_squares;

    m_playableSquares.clear();
    for (int i=0; i<level_rows*level_cols; ++i) {
        PlayableSquare *s = new PlayableSquare;
        s->setActive(false);
        s->setInUse(false);
        if (required_squares.contains(i)) s->setRequired(true);
        m_playableSquares << s;
    }

    //Calculate side col requirements
    int grid_size = level_cols * level_rows;
    QList<PlayableSquare *> mid;
    int n;


    for (int i=0; i<level_rows; ++i) {

    }

    m_lrheaders.clear();
    QList<int> leftReqs;
    for (int r=0; r<level_rows; r++) {
        leftReqs.clear();

        int start = r * level_cols;
        int end = (r+1) * level_cols - 1;
        if (end > grid_size) end = grid_size - 1;
        if (start > m_playableSquares.size()) break;
        mid = m_playableSquares.mid(start, level_cols);
        for (int i = 0; i < mid.size(); ++i) {
            if (mid.at(i)->required()) {
                n = i + 1;
                if (n < mid.size() && mid.at(n)->required()) {
                    int t = 1;
                    while (mid.at(n)->required()) {
                        t += 1;
                        n+=1;
                    }
                    leftReqs.append(t);
                    i=n;
                } else {
                    leftReqs.append(1);
                }
            }
        }

        HeaderGroup *g = new HeaderGroup;
        if (leftReqs.count() > 0) {
            for (int i = 0; i < leftReqs.size(); ++i) {
                g->insertItem(leftReqs.at(i));
            }
        }
        m_lrheaders.insert(r, g);
    }

    QList<int> topReqs;
    m_tbheaders.clear();
    for (int c=0; c<level_cols; c++) {
        topReqs.clear();

        int end = (grid_size - level_cols) + c;

        int x = c;
        bool added = false;
        while (x <= end) {
            added = false;
            if (m_playableSquares.at(x)->required()) {
                n = x + level_cols;
                if (n < m_playableSquares.size() && m_playableSquares.at(n)->required()) {
                    int t = 1;
                    while (m_playableSquares.at(n)->required()) {
                        t += 1;
                        n = (n + level_cols);
                    }
                    topReqs.append(t);
                    x=n;
                } else {
                    topReqs.append(1);
                }
            }

            x += level_cols;
        }

        HeaderGroup *g = new HeaderGroup;
        if (topReqs.count() > 0) {
            for (int i = 0; i < topReqs.size(); ++i) {
                g->insertItem(topReqs.at(i));
            }
        }
        m_tbheaders.insert(c, g);
    }

    m_lvl_cols_left = required_squares.count();
    m_lvl_cols_over = 0;

    emit playableSquaresChanged();
    emit tbHeadersChanged();
    emit lrHeadersChanged();
}

void GameEngine::markPlayableSquare(int index)
{
    //qDebug() << "markPlayableSquare" << index;
    PlayableSquare *s = psquare(index);

    if (!s) return;

    if (!s->inUse()) {
        //qDebug() << "set square" << index << "active";
        s->setActive(true);
        s->setInUse(true);

        if (required_squares.contains(index)) {
            //qDebug() << "found required cell at" << index;
            m_lvl_cols_left -= 1;
        } else {
            m_lvl_cols_over += 1;
        }
    } else {
        if (s->active()) {
            //qDebug() << "set square" << index << "inactive";
            s->setActive(false);

            if (required_squares.contains(index)) {
                //qDebug() << "found required cell at" << index;
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

    //qDebug() << "m_lvl_cols_left:" << m_lvl_cols_left;
    //qDebug() << "m_lvl_cols_over:" << m_lvl_cols_over;
    if (m_lvl_cols_left == 0 && m_lvl_cols_over == 0) {
        //qDebug() << "level finished!";
        emit levelFinished();
    }
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
