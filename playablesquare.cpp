#include "playablesquare.h"

PlayableSquare::PlayableSquare(QObject *parent) :
    QObject(parent),
    m_inuse(false),
    m_active(false)
{
}

int PlayableSquare::getCurrentStatus()
{
    if (!m_inuse) return PSQUARE_STATUS_NOTINUSE;
    if (!m_active) return PSQUARE_STATUS_MARKED;
    return PSQUARE_STATUS_ACTIVE;
}
