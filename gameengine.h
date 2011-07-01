#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <playablesquare.h>
#include <numbersquare.h>
#include <headergroup.h>

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);
    ~GameEngine();

    //void setStorage(Storage *str);

    Q_PROPERTY(QDeclarativeListProperty<PlayableSquare> playableSquares READ playableSquares NOTIFY playableSquaresChanged)
    QDeclarativeListProperty<PlayableSquare> playableSquares() {return QDeclarativeListProperty<PlayableSquare>(this, m_playableSquares);}

    Q_PROPERTY(QDeclarativeListProperty<HeaderGroup> tbHeaders READ tbHeaders NOTIFY tbHeadersChanged)
    QDeclarativeListProperty<HeaderGroup> tbHeaders() {return QDeclarativeListProperty<HeaderGroup>(this, m_tbheaders);}

    Q_PROPERTY(QDeclarativeListProperty<HeaderGroup> lrHeaders READ lrHeaders NOTIFY lrHeadersChanged)
    QDeclarativeListProperty<HeaderGroup> lrHeaders() {return QDeclarativeListProperty<HeaderGroup>(this, m_lrheaders);}

signals:
    void playableSquaresChanged();
    void tbHeadersChanged();
    void lrHeadersChanged();

    void levelFinished();

public slots:
    void markPlayableSquare(int index);
    void markTopColumnSquare(int col, int row);
    void markSideColumnSquare(int row, int col);

private:
    PlayableSquare *psquare(int index) const {return (index >= 0 && index < m_playableSquares.count()) ? m_playableSquares.at(index) : 0;}
    NumberSquare *lrsquare(int row, int col) const {return (row >= 0 && row < m_lrheaders.count()) ? m_lrheaders.at(row)->square(col) : 0;}
    NumberSquare *tbsquare(int col, int row) const {return (col >= 0 && col < m_tbheaders.count()) ? m_tbheaders.at(col)->square(row) : 0;}

    QList<PlayableSquare *> m_playableSquares;

    QList<HeaderGroup *> m_tbheaders;
    QList<HeaderGroup *> m_lrheaders;

    int m_lvl_cols_left;
    int m_lvl_cols_over;
    QList<int> required_squares;

    //Storage* m_storage;

    void m_prepareColumns();
};

#endif // GAMEENGINE_H
