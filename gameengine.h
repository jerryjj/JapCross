#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

#include "level.h"
#include "numbersquare.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);
    ~GameEngine();

    //void setStorage(Storage *str);

    Q_PROPERTY(Level* level READ level NOTIFY levelChanged)
    Level* level() {return m_active_level;}

signals:
    void levelChanged();

    void levelReady();
    void levelFinished();

public slots:
    void loadLevel(int idx);

    void markPlayableCell(int index);
    void markTopColumnSquare(int col, int row);
    void markSideColumnSquare(int row, int col);

    void levelPrepared();
    void levelDone();

private:
    Level* m_active_level;

    NumberSquare *lrsquare(int row, int col) const {return (row >= 0 && row < m_active_level->lrheaders.count()) ? m_active_level->lrheaders.at(row)->square(col) : 0;}
    NumberSquare *tbsquare(int col, int row) const {return (col >= 0 && col < m_active_level->tbheaders.count()) ? m_active_level->tbheaders.at(col)->square(row) : 0;}

    //Storage* m_storage;


};

#endif // GAMEENGINE_H
