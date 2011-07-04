#include <QtGui/QApplication>

#include <mainwidget.h>
#include <levelengine.h>

#include <QFont>

#include <QDesktopWidget>

#include "level.h"
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QString>

#if defined(Q_WS_HARMATTAN)
#include <MDeclarativeCache>
#else
#include <QSplashScreen>
#endif

#include <QTranslator>
#include <QLocale>

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

    //createLevel("/projects/qt/projects/JapCross/levels/default/1.mnl", "Ship", "", 10, 15, QString("139,140,141,142,143,144,145,138,137,121,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,122,123,124,125,126,127,128,129,130,131,132,90,91,96,101,102,76,77,78,79,80,82,83,84,85,86,62,63,64,65,67,68,69,70,48,49,50,52,53,54,34,35,37,38,20,22,6"));
    //createLevel("/projects/qt/projects/JapCross/levels/default/2.mnl", "Bird", "", 15, 15, QString("0,1,2,3,4,5,15,20,21,31,32,33,34,36,39,40,41,43,25,26,27,46,47,52,53,54,55,56,57,58,59,62,63,64,65,66,67,68,69,70,71,72,78,79,81,83,84,85,95,99,100,109,110,113,114,116,117,121,122,123,124,126,127,128,130,132,133,135,136,138,139,140,141,143,144,145,147,149,150,152,153,155,159,160,162,164,165,166,168,170,175,176,177,179,181,182,184,185,191,192,194,197,198,199,207,208,209,223,224"));
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{    
#if defined(Q_WS_HARMATTAN)
    QApplication *a = MDeclarativeCache::qApplication(argc, argv);
    a->setOrganizationName("Infigo");
    a->setOrganizationDomain("infigo.fi");
    a->setApplicationName("MNonograms");
#else
    QApplication a(argc, argv);
    a.setOrganizationName("Infigo");
    a.setOrganizationDomain("infigo.fi");
    a.setApplicationName("MNonograms");
#endif

    QString locale = QLocale::system().name();
    QTranslator translator;

    // Force localization until to english until
    // I figure out why harmattan returns "C" as active locale
#if defined(Q_WS_HARMATTAN)
    Q_UNUSED(locale);
    if (translator.load("qml-translations.en", ":/"))
#else
    if (translator.load(":/qml-translations." + locale, ":/"))
#endif
#if defined(Q_WS_HARMATTAN)
        a->installTranslator(&translator);
#else
        a.installTranslator(&translator);
#endif

    // This is used to generate default levels
    //createLevels();

    QFont newFont("Mangal");
    QApplication::setFont(newFont);

    MainWidget mw;

#if !defined(Q_WS_HARMATTAN)
    // Splash screen
    QPixmap pixmap(":/images/splash-screen-800x480.png");
    QSplashScreen splash(pixmap);
    splash.show();
#endif

#if !defined(Q_WS_HARMATTAN)
    splash.showMessage("Loading levels...");
    a.processEvents();
#endif

    LevelEngine().setLevelsPath("levels/");
    levelEngine().collectLevels();

#if !defined(Q_WS_HARMATTAN)
    splash.showMessage("Levels loaded...");
    a.processEvents();
#endif

    QDesktopWidget *dw = QApplication::desktop();

#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR) || \
    defined(Q_WS_MAEMO_5) || defined(Q_WS_HARMATTAN) || \
    defined(Q_WS_MEEGO)
    mw.setGeometry(dw->geometry());
#else
    Q_UNUSED(dw);
    mw.setGeometry(QRect(0,0,854,480));
    //mw.setGeometry(QRect(0,0,480,854));
#endif

#if !defined(Q_WS_HARMATTAN)
    splash.showMessage("All done");
    a.processEvents();

    splash.finish(&mw);
#endif

#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR) || \
    defined(Q_WS_MAEMO_5) || defined(Q_WS_HARMATTAN)
    mw.showFullScreen();
#else
    mw.show();
#endif

#if defined(Q_WS_HARMATTAN)
    return a->exec();
#else
    return a.exec();
#endif
}
