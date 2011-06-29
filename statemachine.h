#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>

class StateMachine : public QObject
{
    Q_OBJECT
public:
    explicit StateMachine(QObject *parent = 0);

    Q_PROPERTY(bool gameUIVisible READ gameUIVisible WRITE setGameUIVisible NOTIFY gameUIVisibleChanged)
    bool gameUIVisible() const { return m_gameui_visible; }
    void setGameUIVisible(bool state) { if(state==m_gameui_visible) return; m_gameui_visible = state; emit gameUIVisibleChanged(); }

signals:
    void gameUIVisibleChanged();

public slots:

private:
    bool m_gameui_visible;

    StateMachine(const StateMachine&);
    friend StateMachine& stateMachine();
};

StateMachine& stateMachine();

#endif // STATEMACHINE_H
