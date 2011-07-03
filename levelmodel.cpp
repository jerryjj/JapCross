#include "levelmodel.h"

LevelModel::LevelModel(QObject *parent) :
    QObject(parent),
    m_grp(0),
    m_grp_name(""),
    m_lvl(0),
    m_lvl_name(""),
    m_thumbnail(""),
    m_rows(0),
    m_cols(0),
    m_timespent("")

//    m_has_hs(false),
//    m_score(0)
{
}
