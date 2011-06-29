#ifndef PLAYABLESQUARE_H
#define PLAYABLESQUARE_H

#include <QObject>

const int PSQUARE_STATUS_ACTIVE = 1;
const int PSQUARE_STATUS_MARKED = 0;
const int PSQUARE_STATUS_NOTINUSE = -1;

class PlayableSquare : public QObject
{
    Q_OBJECT
public:
    explicit PlayableSquare(QObject *parent = 0);

    Q_PROPERTY(bool inUse READ inUse WRITE setInUse NOTIFY inUseChanged)
    bool inUse() const { return m_inuse; }
    void setInUse(bool state) { if(state==m_inuse) return; m_inuse = state; emit inUseChanged(); }

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    bool active() const { return m_active; }
    void setActive(bool state) { if(state==m_active) return; m_active = state; emit activeChanged(); }

signals:
    void inUseChanged();
    void activeChanged();

public slots:
    int getCurrentStatus();

private:    
    bool m_inuse;
    bool m_active;    
};

#endif // PLAYABLESQUARE_H
