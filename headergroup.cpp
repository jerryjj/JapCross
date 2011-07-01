#include "headergroup.h"

HeaderGroup::HeaderGroup(QObject *parent) :
    QObject(parent)
{
}

void HeaderGroup::insertItem(int val)
{
    NumberSquare *s = new NumberSquare;
    s->setInUse(true);
    s->setValue(val);
    m_items << s;

    emit itemsChanged();
}

int HeaderGroup::itemCount()
{
    return m_items.size();
}
