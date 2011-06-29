#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <playablesquare.h>
#include <numbersquare.h>

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);
    ~GameEngine();

    //void setStorage(Storage *str);

    Q_PROPERTY(QDeclarativeListProperty<PlayableSquare> playableSquares READ playableSquares NOTIFY playableSquaresChanged)
    QDeclarativeListProperty<PlayableSquare> playableSquares() {return QDeclarativeListProperty<PlayableSquare>(this, m_playableSquares);}

    Q_PROPERTY(QDeclarativeListProperty<NumberSquare> topColumns READ topColumns NOTIFY topColumnsChanged)
    QDeclarativeListProperty<NumberSquare> topColumns() {return QDeclarativeListProperty<NumberSquare>(this, m_topColumns);}

    Q_PROPERTY(QDeclarativeListProperty<NumberSquare> sideColumns READ sideColumns NOTIFY sideColumnsChanged)
    QDeclarativeListProperty<NumberSquare> sideColumns() {return QDeclarativeListProperty<NumberSquare>(this, m_sideColumns);}

signals:
    void playableSquaresChanged();
    void topColumnsChanged();
    void sideColumnsChanged();

public slots:
    void markPlayableSquare(int index);
    void markTopColumnSquare(int index);
    void markSideColumnSquare(int index);

private:
    PlayableSquare *psquare(int index) const {return (index >= 0 && index < m_playableSquares.count()) ? m_playableSquares.at(index) : 0;}
    NumberSquare *snsquare(int index) const {return (index >= 0 && index < m_sideColumns.count()) ? m_sideColumns.at(index) : 0;}
    NumberSquare *tnsquare(int index) const {return (index >= 0 && index < m_topColumns.count()) ? m_topColumns.at(index) : 0;}

    QList<PlayableSquare *> m_playableSquares;
    QList<NumberSquare *> m_sideColumns;
    QList<NumberSquare *> m_topColumns;

    //Storage* m_storage;

    void m_prepareColumns();
};

#endif // GAMEENGINE_H
