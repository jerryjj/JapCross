#include <QtGui/QApplication>

#include <mainwidget.h>
#include <levelengine.h>

#include <QFont>
//#include <QSplashScreen>

#include <QDesktopWidget>

#include "level.h"
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QString>

void createLevel(QString path, QString name, QString author, int rows, int cols, QString req_cells)
{
    qDebug() << "create level ";
    QFile file(path);
    qDebug() << path;
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    stream << (quint32) 0xA0B0C0D0; stream << (quint32) 100;
    stream.setVersion(QDataStream::Qt_4_7);

    Level lvl;

    lvl.setName(name);
    lvl.setAuthor(author);
    lvl.setLevelData(rows, cols, req_cells.split(","));

    stream << lvl;
}

void createLevels()
{
    //Test level (X)
    //createLevel("/projects/qt/projects/JapCross/levels/default/1.mnl", "Test level - X", "Jerry Jalava", 10, 10, QString("0,9,11,18,22,27,33,36,44,45,55,54,66,63,77,72,88,81,99,90"));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Splash screen
    //QPixmap pixmap(":/images/splash-screen-800x480.png");
    //QSplashScreen splash(pixmap);
    //splash.show();

    // This is used to generate default levels
    //createLevels();

    QFont newFont("Mangal");
    QApplication::setFont(newFont);

    a.setOrganizationName("Infigo");
    a.setOrganizationDomain("infigo.fi");
    a.setApplicationName("MNonograms");

    MainWidget mw;

    //splash.showMessage("Loading levels...");
    //a.processEvents();

    LevelEngine().setLevelsPath("levels/");
    levelEngine().collectLevels();

    //splash.showMessage("Levels loaded...");
    //a.processEvents();

    QDesktopWidget *dw = QApplication::desktop();

    //splash.showMessage("Preparing geometries...");
    //a.processEvents();

#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR) || \
    defined(Q_WS_MAEMO_5) || defined(Q_WS_HARMATTAN) || \
    defined(Q_WS_MEEGO)
    mw.setGeometry(dw->geometry());
#else
    Q_UNUSED(dw);
    mw.setGeometry(QRect(0,0,854,480));
#endif

    //splash.showMessage("All done");
    //a.processEvents();

    //splash.finish(&mw);

#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR) || \
    defined(Q_WS_MAEMO_5) || defined(Q_WS_HARMATTAN)
    mw.showFullScreen();
#else
    mw.show();
#endif

    return a.exec();
}
