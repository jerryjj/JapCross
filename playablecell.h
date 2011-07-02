#ifndef PLAYABLECELL_H
#define PLAYABLECELL_H

#include <QObject>

const int PCQUARE_STATUS_ACTIVE = 1;
const int PCQUARE_STATUS_MARKED = 0;
const int PCQUARE_STATUS_NOTINUSE = -1;

class PlayableCell : public QObject
{
    Q_OBJECT
public:
    explicit PlayableCell(QObject *parent = 0);

    Q_PROPERTY(bool inUse READ inUse WRITE setInUse NOTIFY inUseChanged)
    bool inUse() const { return m_inuse; }
    void setInUse(bool state) { if(state==m_inuse) return; m_inuse = state; emit inUseChanged(); }

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    bool active() const { return m_active; }
    void setActive(bool state) { if(state==m_active) return; m_active = state; emit activeChanged(); }

    Q_PROPERTY(bool required READ required WRITE setRequired NOTIFY requiredChanged)
    bool required() const { return m_required; }
    void setRequired(bool state) { if(state==m_required) return; m_required = state; emit requiredChanged(); }

signals:
    void inUseChanged();
    void activeChanged();
    void requiredChanged();

public slots:
    int getCurrentStatus();

private:
    bool m_inuse;
    bool m_active;
    bool m_required;

};

#endif // PLAYABLECELL_H
