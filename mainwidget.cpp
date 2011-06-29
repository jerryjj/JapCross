#include "mainwidget.h"

#include <QDeclarativeItem>
#include <QGLWidget>
#include <QGLFormat>
#include <QUrl>
#include <QApplication>
#include <QDeclarativeEngine>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <gameengine.h>
#include <playablesquare.h>
#include <statemachine.h>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QDeclarativeView(parent)
{
    // Switch to fullscreen in device
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
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

    qmlRegisterType<PlayableSquare>("gameCore", 1, 0, "PlayableSquare");

    // Setup context
    m_context = rootContext();
    m_context->setContextProperty("mw", this);
    m_context->setContextProperty("gameEngine", &m_gameEngine);
    m_context->setContextProperty("stateMachine", &stateMachine());

    // Set view optimizations not already done for QDeclarativeView
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set auto orientation
    Qt::WidgetAttribute attribute;
#if QT_VERSION < 0x040702
    attribute = static_cast<Qt::WidgetAttribute>(130);
#else
    attribute = Qt::WA_AutoOrientation;
#endif
    setAttribute(attribute, true);

#if defined(OPENGL_ENABLED)
    // Make QDeclarativeView use OpenGL backend
    QGLWidget *glWidget = new QGLWidget(this);
    setViewport(glWidget);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
#endif

    // Open root QML file
    QString mainqml(m_adjustPath(uiPath + "main.qml"));
    setSource(QUrl(mainqml)); //QUrl::fromLocalFile

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
