#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <playablecell.h>
#include <numbersquare.h>
#include <headergroup.h>

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

    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
    int rows() {return m_rows;}

    Q_PROPERTY(int cols READ cols NOTIFY colsChanged)
    int cols() {return m_cols;}

signals:
    void playableCellsChanged();
    void tbHeadersChanged();
    void lrHeadersChanged();

    void rowsChanged();
    void colsChanged();

    void prepared();
    void finished();

public slots:
    void markPlayableCell(int index);
    void setLevelData(int rows, int cols, QString req_cells);

public:
    QList<HeaderGroup *> tbheaders;
    QList<HeaderGroup *> lrheaders;

protected:
    int cols_left;
    int cols_over;

private:
    PlayableCell *psquare(int index) const {return (index >= 0 && index < m_playable_cells.count()) ? m_playable_cells.at(index) : 0;}

    int m_rows;
    int m_cols;

    QList<int> m_required_cells;
    QList<PlayableCell *> m_playable_cells;

    QString m_picture_cells;

    void m_prepareCells();

};

#endif // LEVEL_H
