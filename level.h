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

signals:
    void playableCellsChanged();
    void tbHeadersChanged();
    void lrHeadersChanged();
    void nameChanged();

    void rowsChanged();
    void colsChanged();

    void timespentChanged();

    void prepared();
    void finished();

public slots:
    void markPlayableCell(int index);
    void setLevelData(int rows, int cols, QStringList req_cells);

    bool prepare();

    void timerUpdated();

public:
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

    QString m_name;
    QString m_author;

    int m_timespent;
    QTimer *m_timer;
};

QDataStream &operator << (QDataStream &out, const Level &lvl);
QDataStream &operator >> (QDataStream &in, Level &lvl);

#endif // LEVEL_H
