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

    Q_PROPERTY(bool gameInProgress READ gameInProgress WRITE setGameInProgress NOTIFY gameInProgressChanged)
    bool gameInProgress() const { return m_game_in_progress; }
    void setGameInProgress(bool state) { if(state==m_game_in_progress) return; m_game_in_progress = state; emit gameInProgressChanged(); }

    Q_PROPERTY(bool loadingLevel READ loadingLevel WRITE setLoadingLevel NOTIFY loadingLevelChanged)
    bool loadingLevel() const { return m_loading_level; }
    void setLoadingLevel(bool state) { if(state==m_loading_level) return; m_loading_level = state; emit loadingLevelChanged(); }

signals:
    void gameUIVisibleChanged();
    void gameInProgressChanged();
    void loadingLevelChanged();

public slots:

private:
    bool m_gameui_visible;
    bool m_game_in_progress;
    bool m_loading_level;

    StateMachine(const StateMachine&);
    friend StateMachine& stateMachine();
};

StateMachine& stateMachine();

#endif // STATEMACHINE_H
