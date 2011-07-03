#include "statemachine.h"

StateMachine::StateMachine(QObject *parent) :
    QObject(parent),
    m_gameui_visible(false),
    m_game_in_progress(false),
    m_loading_level(false)
{
}

StateMachine& stateMachine() {
    static StateMachine sm;
    return sm;
};
