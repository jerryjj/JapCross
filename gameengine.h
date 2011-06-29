#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <playablesquare.h>

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);
    ~GameEngine();

    //void setStorage(Storage *str);

    Q_PROPERTY(QDeclarativeListProperty<PlayableSquare> playableSquares READ playableSquares NOTIFY playableSquaresChanged)
    QDeclarativeListProperty<PlayableSquare> playableSquares() {return QDeclarativeListProperty<PlayableSquare>(this, m_playableSquares);}

signals:
    void playableSquaresChanged();

public slots:
    void markPlayableSquare(int index);

private:
    PlayableSquare *psquare(int index) const {return (index >= 0 && index < m_playableSquares.count()) ? m_playableSquares.at(index) : 0;}

    QList<PlayableSquare *> m_playableSquares;
    //Storage* m_storage;

    void m_preparePlayableSquares();
};

#endif // GAMEENGINE_H
