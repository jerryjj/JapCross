# Add more folders to ship with the application, here
folder_01.source = qml/JapCross
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE73FCB26

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

contains(QT_CONFIG, opengles2)|contains(QT_CONFIG, opengl):DEFINES += OPENGL_ENABLED
contains(DEFINES, OPENGL_ENABLED):QT += opengl

contains(QT, opengl) {
     message(Building with OpenGL support.)
 } else {
     message(OpenGL support is not available.)
 }

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    gameengine.cpp \
    playablesquare.cpp \
    statemachine.cpp \
    mainwidget.cpp \
    numbersquare.cpp \
    headergroup.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    gameengine.h \
    playablesquare.h \
    statemachine.h \
    mainwidget.h \
    numbersquare.h \
    headergroup.h

RESOURCES += \
    assets.qrc \
    ui.qrc

maemo5 {
    icon.files = icons/icon-64x64.png
    icon.path = /usr/share/icons/hicolor/64x64/apps

    INSTALLS += \
        icon
}

# Harmattan
unix:!symbian:!maemo5:!macx {
    message(Harmattan build)
    DEFINES += Q_WS_HARMATTAN

    RESOURCES += harmattan.qrc
    OTHER_FILES += \
        qml/JapCross/harmattan.qml

    target.path = /opt/usr/bin

    desktopfile.files = qtc_packaging/debian_harmattan/$${TARGET}.desktop
    desktopfile.path = /usr/share/applications

    icon.files = icons/icon-harmattan-64x64.png
    icon.path = /usr/share/icons/hicolor/64x64/apps

    INSTALLS += \
        target \
        desktopfile \
        icon

    # enable booster
    CONFIG += qdeclarative-boostable
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic
} else {
    message(Desktop build)
    RESOURCES += no_components.qrc
    OTHER_FILES += \
        qml/JapCross/no_components.qml
}
