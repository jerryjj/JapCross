#include "playablecell.h"

PlayableCell::PlayableCell(QObject *parent) :
    QObject(parent),
    m_inuse(false),
    m_active(false),
    m_required(false)
{
}

int PlayableCell::getCurrentStatus()
{
    if (!m_inuse) return PCQUARE_STATUS_NOTINUSE;
    if (!m_active) return PCQUARE_STATUS_MARKED;
    return PCQUARE_STATUS_ACTIVE;
}
