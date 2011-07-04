#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QStringList>
#include <QDataStream>
#include <QDeclarativeListProperty>
#include <QTimer>

#include <playablecell.h>
#include <numbersquare.h>
#include <headergroup.h>

typedef QList<int> lvlReqCells;

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);

    Q_PROPERTY(QDeclarativeListProperty<PlayableCell> playableCells READ playableCells NOTIFY playableCellsChanged)
    QDeclarativeListProperty<PlayableCell> playableCells() {return QDeclarativeListProperty<PlayableCell>(this, m_playable_cells);}

    Q_PROPERTY(QDeclarativeListProperty<HeaderGroup> tbHeaders READ tbHeaders NOTIFY tbHeadersChanged)
    QDeclarativeListProperty<HeaderGroup> tbHeaders() {return QDeclarativeListProperty<HeaderGroup>(this, tbheaders);}

    Q_PROPERTY(QDeclarativeListProperty<HeaderGroup> lrHeaders READ lrHeaders NOTIFY lrHeadersChanged)
    QDeclarativeListProperty<HeaderGroup> lrHeaders() {return QDeclarativeListProperty<HeaderGroup>(this, lrheaders);}

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QString name() const {return m_name;}
    void setName(QString v) { m_name = v; emit nameChanged(); }

    Q_PROPERTY(QString author READ author WRITE setAuthor)
    QString author() const {return m_author;}
    void setAuthor(QString v) { m_author = v; }

    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
    int rows() const {return m_rows;}

    Q_PROPERTY(int cols READ cols NOTIFY colsChanged)
    int cols() const {return m_cols;}

    Q_PROPERTY(int timespent READ timespent NOTIFY timespentChanged)
    int timespent() const {return m_timespent;}
    void setTimespent(int v) { m_timespent = v; }

    Q_PROPERTY(bool levelFinished READ levelFinished NOTIFY levelFinishedChanged)
    bool levelFinished() const {return m_finished;}
    void setLevelFinished(bool v) { m_finished = v; emit levelFinishedChanged(); }

    int colsLeft() const {return cols_left;}
    void setColsLeft(int v) { cols_left = v; }
    int colsOver() const {return cols_over;}
    void setColsOver(int v) { cols_over = v; }

    QStringList usedCells() {return m_used_cells;}
    void setUsedCells(QStringList v) { m_used_cells = v; }
    QStringList markedCells() {return m_marked_cells;}
    void setMarkedCells(QStringList v) { m_marked_cells = v; }

signals:
    void playableCellsChanged();
    void tbHeadersChanged();
    void lrHeadersChanged();
    void nameChanged();

    void rowsChanged();
    void colsChanged();

    void timespentChanged();

    void levelFinishedChanged();

    void prepared();
    void finished();

public slots:
    void markPlayableCell(int index);
    void setLevelData(int rows, int cols, QStringList req_cells);

    bool prepare();

    void timerUpdated();

    void pauseLevel();
    void continueLevel();

public:
    int grp;
    int lvl;

    QList<HeaderGroup *> tbheaders;
    QList<HeaderGroup *> lrheaders;
    QStringList required_cells_sl;

protected:
    int cols_left;
    int cols_over;

private:
    PlayableCell *psquare(int index) const {return (index >= 0 && index < m_playable_cells.count()) ? m_playable_cells.at(index) : 0;}

    int m_rows;
    int m_cols;

    lvlReqCells m_required_cells;
    QList<PlayableCell *> m_playable_cells;

    QStringList m_used_cells;
    QStringList m_marked_cells;

    QString m_name;
    QString m_author;

    int m_timespent;
    QTimer *m_timer;

    bool m_paused;
    bool m_finished;
};

QDataStream &operator << (QDataStream &out, const Level &lvl);
QDataStream &operator >> (QDataStream &in, Level &lvl);

#endif // LEVEL_H
