import QtQuick 1.0

import "Menu" 1.0 as Menu

AppWindow {
    id: main

    property bool portrait: true

    Component.onCompleted: {
        menuPanel.state = "showMain";
    }

    onWindowactiveChanged: {
        if (! windowactive) {
            gameEngine.pauseGame();
        } else {
            gameEngine.continueGame();
        }
    }

    Connections {
        target: gameEngine

        onLevelLoading: {
            gameBoard.enabled = false;
        }

        onLevelReady: {
            gameBoard.enabled = true;
        }
    }

    Image {
        id: background
        anchors.fill: parent
        source: "images/background.png"
        //fillMode: Image.PreserveAspectCrop

        onHeightChanged: {
            main.portrait = (width < height);
            //console.debug("main.qml:Image:onHeightChanged(): [", width, ",", height, "], portrait ==", portrait);
        }
    }

    Item {
        id: levelLoading

        width: loadingTxt.width + 20; height: loadingTxt.height + 20
        anchors.centerIn: parent
        opacity: 0; scale: 0

        Rectangle {
            anchors.fill: parent
            radius: 10
            smooth: true
            opacity: 0.8
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#505050" }
                GradientStop { position: 1.0; color: "#505050" }
            }
        }

        Text {
            id: loadingTxt
            anchors.centerIn: parent
            color: "#fff"
            text: qsTr("Loading level")
            font.pointSize: 40
        }

        Timer {
            id: llTimer
            repeat: false
            interval: 500; running: false
            triggeredOnStart: false

            onTriggered: {
                gameEngine.startLevelLoad();
            }
        }

        states: [
            State {
                name: "visible"
                when: stateMachine.loadingLevel
                PropertyChanges {
                    target: levelLoading
                    opacity: 1
                    scale: 1.0
                }
                PropertyChanges {
                    target: llTimer
                    running: true
                }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                properties: "opacity,scale"
                duration: 400
            }
        }
    }

    Item {
        id: clearLevelConfirm
        width: portrait ? parent.width - 50 : parent.width - 200
        height: 130
        anchors.centerIn: parent
        z: 100
        opacity: 0

        Rectangle {
            color: "#fff"
            border.width: 1
            border.color: "#abacad"
            anchors.fill: parent
        }

        Text {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 - width / 2
            id: clearTxt
            font.family: "nokia"
            font.pointSize: 26
            font.bold: true
            smooth: true
            color: "#562a7a"
            text: qsTr("Really clear the level?")
        }

        Row {
            width: parent.width - 100
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 - width / 2
            anchors.top: clearTxt.bottom
            anchors.topMargin: 10
            spacing: 10

            Menu.Button {
                id: btnClearLevelConfirm
                width: parent.width / 2 - 5
                text: qsTr("Yes")
                disabled: false
                onClicked: {
                    clearLevelConfirm.opacity = 0;
                    gameEngine.clearGameState();
                }
            }
            Menu.Button {
                id: btnClearLevelCancel
                width: parent.width / 2 - 5
                text: qsTr("Cancel")
                disabled: false
                onClicked: {
                    clearLevelConfirm.opacity = 0;
                }
            }
        }

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 300
            }
        }
    }

    Item {
        id: gameUI
        anchors.fill: parent
        opacity: 0

        GameBoard {
            id: gameBoard
            enabled: false
        }

        states: [
            State {
                name: "visible"
                when: stateMachine.gameUIVisible
                PropertyChanges {
                    target: gameUI
                    opacity: 1
                }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 300
            }
        }
    }

    Menu.Main {
        id: menuPanel
    }
}
