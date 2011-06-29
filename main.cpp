#include <QtGui/QApplication>
//#include "qmlapplicationviewer.h"

#include <mainwidget.h>

#include <QFont>
#include <QSplashScreen>

#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/JapCross/main.qml"));
    viewer.showExpanded();*/

    // Splash screen
    QPixmap pixmap(":/images/splash-screen-800x480.png");
    QSplashScreen splash(pixmap);
    splash.show();

    QFont newFont("Mangal");
    QApplication::setFont(newFont);

    a.setOrganizationName("Infigo Finland Oy");
    a.setOrganizationDomain("infigo.fi");
    a.setApplicationName("Japanese Crosswords");

    MainWidget mw;

    //splash.showMessage("Loading levels...");
    //a.processEvents();

    //TODO: Load levels

    //splash.showMessage("Levels loaded...");
    //a.processEvents();

    QDesktopWidget *dw = QApplication::desktop();

    splash.showMessage("Preparing geometries...");
    a.processEvents();

#if defined(Q_WS_S60)
    mw.setGeometry(dw->geometry());
#elif defined(Q_WS_MAEMO_5)
    mw.setGeometry(dw->geometry());
#elif defined(Q_WS_MEEGO) || defined(Q_WS_MAEMO_6)
    mw.setGeometry(dw->geometry());
#else
    Q_UNUSED(dw);
    mw.setGeometry(QRect(0,0,800,600));
#endif

    splash.showMessage("All done");
    a.processEvents();

#if defined(Q_WS_S60)
    mw.showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    mw.showFullScreen();
#elif defined(Q_WS_MEEGO) || defined(Q_WS_MAEMO_6)
    mw.showFullScreen();
#else
    mw.show();
#endif

    splash.finish(&mw);

    return a.exec();
}
