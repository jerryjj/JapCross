#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#include <QObject>

class LevelModel : public QObject
{
    Q_OBJECT
public:
    explicit LevelModel(QObject *parent = 0);

    Q_PROPERTY(int grp READ grp WRITE setGrp NOTIFY grpChanged)
    int grp() const { return m_grp; }
    void setGrp(int v) { m_grp = v; emit grpChanged(); }

    Q_PROPERTY(QString grpName READ grpName WRITE setGrpName NOTIFY grpNameChanged)
    QString grpName() const { return m_grp_name; }
    void setGrpName(QString v) { m_grp_name = v; emit grpNameChanged(); }

    Q_PROPERTY(int lvl READ lvl WRITE setLvl NOTIFY lvlChanged)
    int lvl() const { return m_lvl; }
    void setLvl(int v) { m_lvl = v; emit lvlChanged(); }

    Q_PROPERTY(QString lvlName READ lvlName WRITE setLvlName NOTIFY lvlNameChanged)
    QString lvlName() const { return m_lvl_name; }
    void setLvlName(QString v) { m_lvl_name = v; emit lvlNameChanged(); }

    Q_PROPERTY(QString thumbnail READ thumbnail WRITE setThumbnail NOTIFY thumbnailChanged)
    QString thumbnail() const { return m_thumbnail; }
    void setThumbnail(QString v) { m_thumbnail = v; emit thumbnailChanged(); }

    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    int rows() const { return m_rows; }
    void setRows(int v) { m_rows = v; emit rowsChanged(); }

    Q_PROPERTY(int cols READ cols WRITE setCols NOTIFY colsChanged)
    int cols() const { return m_cols; }
    void setCols(int v) { m_cols = v; emit colsChanged(); }

    Q_PROPERTY(QString timespent READ timespent WRITE setTimespent NOTIFY timespentChanged)
    QString timespent() const { return m_timespent; }
    void setTimespent(QString v) { m_timespent = v; emit timespentChanged(); }

//    Q_PROPERTY(bool hasHighscore READ hasHighscore WRITE setHasHighscore NOTIFY hasHighscoreChanged)
//    bool hasHighscore() const { return m_has_hs; }
//    void setHasHighscore(bool state) { if(state==m_has_hs) return; m_has_hs = state; emit hasHighscoreChanged(); }

//    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
//    int score() const { return m_score; }
//    void setScore(int v) { m_score = v; emit scoreChanged(); }

signals:
    void grpChanged();
    void grpNameChanged();
    void lvlChanged();
    void lvlNameChanged();
    void thumbnailChanged();
    void rowsChanged();
    void colsChanged();
    void timespentChanged();

//    void hasHighscoreChanged();
//    void scoreChanged();

private:
    int m_grp;
    QString m_grp_name;
    int m_lvl;
    QString m_lvl_name;
    QString m_thumbnail;
    int m_rows;
    int m_cols;
    QString m_timespent;

//    bool m_has_hs;
//    int m_score;

};

#endif // LEVELMODEL_H
