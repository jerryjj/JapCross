#include <QtGui/QApplication>

#include <mainwidget.h>

#include <QFont>
//#include <QSplashScreen>

#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Splash screen
    //QPixmap pixmap(":/images/splash-screen-800x480.png");
    //QSplashScreen splash(pixmap);
    //splash.show();

    QFont newFont("Mangal");
    QApplication::setFont(newFont);

    a.setOrganizationName("Infigo Finland Oy");
    a.setOrganizationDomain("infigo.fi");
    a.setApplicationName("MNonograms");

    MainWidget mw;

    //splash.showMessage("Loading levels...");
    //a.processEvents();

    //TODO: Load levels

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
