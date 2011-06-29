#include "numbersquare.h"

NumberSquare::NumberSquare(QObject *parent) :
    QObject(parent),
    m_inuse(false),
    m_marked(false),
    m_value(0)
{
}

int NumberSquare::getCurrentStatus()
{
  if (!m_inuse) return NSQUARE_STATUS_NOTINUSE;
  if (!m_marked) return NSQUARE_STATUS_MARKED;
  return NSQUARE_STATUS_ACTIVE;
}
