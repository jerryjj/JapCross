#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDeclarativeView>
#include <QDeclarativeContext>

#include <gameengine.h>

//const QString uiPath = "qrc:/ui/";
const QString uiPath = "qml/JapCross/";

class MainWidget : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

signals:

public slots:
    void exitApplication();

private:
    QDeclarativeContext *m_context;
    GameEngine m_gameEngine;

    //Storage m_storage;

    QString m_adjustPath(const QString &path);
};

#endif // MAINWIDGET_H
