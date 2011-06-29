#include "statemachine.h"

StateMachine::StateMachine(QObject *parent) :
    QObject(parent),
    m_gameui_visible(false)
{
}

StateMachine& stateMachine() {
    static StateMachine sm;
    return sm;
};
