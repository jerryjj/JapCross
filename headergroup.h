#ifndef HEADERGROUP_H
#define HEADERGROUP_H

#include <QObject>
#include <QDeclarativeListProperty>

#include <numbersquare.h>
#include <QDebug>

class HeaderGroup : public QObject
{
    Q_OBJECT
public:
    explicit HeaderGroup(QObject *parent = 0);

    Q_PROPERTY(QDeclarativeListProperty<NumberSquare> items READ items NOTIFY itemsChanged)
    QDeclarativeListProperty<NumberSquare> items() {return QDeclarativeListProperty<NumberSquare>(this, m_items);}

signals:
    void itemsChanged();

public slots:
    void insertItem(int val);
    int itemCount();

public:
    NumberSquare *square(int idx) const {return (idx >= 0 && idx < m_items.count()) ? m_items.at(idx) : 0;}

private:
    QList<NumberSquare *> m_items;

};

#endif // HEADERGROUP_H
