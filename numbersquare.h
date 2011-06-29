#ifndef NUMBERSQUARE_H
#define NUMBERSQUARE_H

#include <QObject>

const int NSQUARE_STATUS_ACTIVE = 0;
const int NSQUARE_STATUS_MARKED = 1;
const int NSQUARE_STATUS_NOTINUSE = -1;

class NumberSquare : public QObject
{
    Q_OBJECT
public:
    explicit NumberSquare(QObject *parent = 0);

    Q_PROPERTY(bool inUse READ inUse WRITE setInUse NOTIFY inUseChanged)
    bool inUse() const { return m_inuse; }
    void setInUse(bool state) { if(state==m_inuse) return; m_inuse = state; emit inUseChanged(); }

    Q_PROPERTY(bool marked READ marked WRITE setMarked NOTIFY markedChanged)
    bool marked() const { return m_marked; }
    void setMarked(bool state) { if(state==m_marked) return; m_marked = state; emit markedChanged(); }

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    int value() const { return m_value; }
    void setValue(int val) { if(val==m_value) return; m_value = val; emit valueChanged(); }

signals:
    void inUseChanged();
    void markedChanged();
    void valueChanged();

public slots:
    int getCurrentStatus();

private:
    bool m_inuse;
    bool m_marked;
    int m_value;
};

#endif // NUMBERSQUARE_H
