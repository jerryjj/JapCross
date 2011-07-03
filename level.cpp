#include "level.h"

#include <QStringListIterator>

Level::Level(QObject *parent) :
    QObject(parent),
    m_rows(0),
    m_cols(0)
{
}

void Level::setLevelData(int rows, int cols, QStringList req_cells)
{
    m_rows = rows;
    m_cols = cols;

    required_cells_sl = req_cells;
    m_required_cells.clear();
    QStringListIterator it(req_cells);
    while (it.hasNext())
        m_required_cells << it.next().toInt();
}

void Level::markPlayableCell(int index)
{
    //qDebug() << "Level::markPlayableCell" << index;
    PlayableCell *s = psquare(index);

    if (!s) return;

    if (!s->inUse()) {
        //qDebug() << "set square" << index << "active";
        s->setActive(true);
        s->setInUse(true);

        if (m_required_cells.contains(index)) {
            //qDebug() << "found required cell at" << index;
            cols_left -= 1;
        } else {
            cols_over += 1;
        }
    } else {
        if (s->active()) {
            //qDebug() << "set square" << index << "inactive";
            s->setActive(false);

            if (m_required_cells.contains(index)) {
                //qDebug() << "found required cell at" << index;
                cols_left += 1;
            } else {
                cols_over -= 1;
            }
        } else {
            //qDebug() << "set square" << index << "disabled";
            s->setActive(false);
            s->setInUse(false);
        }
    }

    //qDebug() << "cols_left:" << cols_left;
    //qDebug() << "cols_over:" << cols_over;
    if (cols_left == 0 && cols_over == 0) {
        emit finished();
    }
}

bool Level::prepare()
{
    if (m_rows == 0 || m_cols == 0 || m_required_cells.size() == 0) {
        return false;
    }

    m_playable_cells.clear();
    lrheaders.clear();
    tbheaders.clear();

    int cell_count = m_cols * m_rows;

    for (int i=0; i<cell_count; ++i) {
        PlayableCell *s = new PlayableCell;
        s->setActive(false);
        s->setInUse(false);
        if (m_required_cells.contains(i)) s->setRequired(true);
        m_playable_cells << s;
    }

    QList<PlayableCell *> mid;

    QList<int> leftReqs;
    for (int r=0; r<m_rows; r++) {
        leftReqs.clear();

        int start = r * m_cols;
        int end = (r+1) * m_cols - 1;
        if (end > cell_count) end = cell_count - 1;
        if (start > m_playable_cells.size()) break;
        mid = m_playable_cells.mid(start, m_cols);
        for (int i = 0; i < mid.size(); ++i) {
            if (mid.at(i)->required()) {
                int n = i + 1;
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
        } else {
            g->insertItem(0);
        }
        lrheaders.insert(r, g);
    }

    QList<int> topReqs;
    for (int c=0; c<m_cols; c++) {
        topReqs.clear();

        int end = (cell_count - m_cols) + c;

        int x = c;
        bool added = false;
        while (x <= end) {
            added = false;
            if (m_playable_cells.at(x)->required()) {
                int n = x + m_cols;
                if (n < m_playable_cells.size() && m_playable_cells.at(n)->required()) {
                    int t = 1;
                    while (m_playable_cells.at(n)->required()) {
                        t += 1;
                        n = (n + m_cols);
                    }
                    topReqs.append(t);
                    x=n;
                } else {
                    topReqs.append(1);
                }
            }

            x += m_cols;
        }

        HeaderGroup *g = new HeaderGroup;
        if (topReqs.count() > 0) {
            for (int i = 0; i < topReqs.size(); ++i) {
                g->insertItem(topReqs.at(i));
            }
        } else {
            g->insertItem(0);
        }
        tbheaders.insert(c, g);
    }

    cols_left = m_required_cells.count();
    cols_over = 0;

    emit playableCellsChanged();
    emit tbHeadersChanged();
    emit lrHeadersChanged();

    emit prepared();

    return true;
}

QDataStream &operator << (QDataStream &out, const Level &lvl)
{
    out << lvl.name() << lvl.author() << lvl.rows() << lvl.cols() << lvl.required_cells_sl;
    return out;
}

QDataStream &operator >> (QDataStream &in, Level &lvl)
{
    QString name;
    QString author;
    int rows;
    int cols;
    QStringList req_cells;

    in >> name >> author >> rows >> cols >> req_cells;

    lvl.setName(name);
    lvl.setAuthor(author);
    lvl.setLevelData(rows, cols, req_cells);

    return in;
}
