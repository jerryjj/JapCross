#include "mainwidget.h"

#include <QDeclarativeItem>

#if defined(OPENGL_ENABLED)
#include <QGLWidget>
#include <QGLFormat>
#endif

#include <QUrl>
#include <QApplication>
#include <QDeclarativeEngine>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <gameengine.h>
#include <levelengine.h>
#include <statemachine.h>

#include <level.h>
#include <levelmodel.h>
#include <playablecell.h>
#include <numbersquare.h>
#include <headergroup.h>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QDeclarativeView(parent)
{
    // Switch to fullscreen in device
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR) || defined(Q_WS_MEEGO) || defined(Q_WS_HARMATTAN)
    setWindowState(Qt::WindowFullScreen);
#endif

    /*
    if (m_storage.connect()) {
        //m_storage.uninstall();
        m_storage.initialize();
    }
    m_gameEngine.setStorage(&m_storage);
    */

    setResizeMode(QDeclarativeView::SizeRootObjectToView);

    qmlRegisterType<Level>("gameCore", 1, 0, "Level");
    qmlRegisterType<LevelModel>("gameCore", 1, 0, "LevelModel");
    qmlRegisterType<PlayableCell>("gameCore", 1, 0, "PlayableCell");
    qmlRegisterType<NumberSquare>("gameCore", 1, 0, "NumberSquare");
    qmlRegisterType<HeaderGroup>("gameCore", 1, 0, "HeaderGroup");

    // Setup context
    m_context = rootContext();
    m_context->setContextProperty("mw", this);
    m_context->setContextProperty("gameEngine", &m_gameEngine);
    m_context->setContextProperty("levelEngine", &levelEngine());
    m_context->setContextProperty("stateMachine", &stateMachine());

    // Set view optimizations not already done for QDeclarativeView
#if !defined(Q_WS_MEEGO) && !defined(Q_WS_HARMATTAN)
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
#endif

#if !defined(Q_WS_MEEGO) && !defined(Q_WS_HARMATTAN)
    // Set auto orientation
    Qt::WidgetAttribute attribute;
#if QT_VERSION < 0x040702
    attribute = static_cast<Qt::WidgetAttribute>(130);
#else
    attribute = Qt::WA_AutoOrientation;
#endif
    setAttribute(attribute, true);
#endif

#if defined(OPENGL_ENABLED)
    // Make QDeclarativeView use OpenGL backend
    QGLWidget *glWidget = new QGLWidget(this);
    setViewport(glWidget);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
#endif

    setSource(QUrl(uiPath + "main.qml"));

    stateMachine().setLoadingLevel(false);

    connect(engine(), SIGNAL(quit()), SLOT(close()));
}

MainWidget::~MainWidget()
{
    //m_storage.disconnect();
}

void MainWidget::exitApplication()
{
    //m_gameEngine.saveGameState();
    QApplication::quit();
}

QString MainWidget::m_adjustPath(const QString &path)
{
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
    if (!QDir::isAbsolutePath(path))
        return QCoreApplication::applicationDirPath()
                + QLatin1String("/../Resources/") + path;
#else
    const QString pathInInstallDir = QCoreApplication::applicationDirPath()
        + QLatin1String("/../") + path;
    if (pathInInstallDir.contains(QLatin1String("opt"))
            && pathInInstallDir.contains(QLatin1String("bin"))
            && QFileInfo(pathInInstallDir).exists()) {
        return pathInInstallDir;
    }
#endif
#endif
    return path;
}
