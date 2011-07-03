import QtQuick 1.0

import "Menu" 1.0 as Menu

Item {
    id: gameBoard
    anchors.fill: parent

    opacity: 0
    scale: 1.0

    GameHud {
        id: gameHud
        anchors.top: parent.top
        anchors.right: parent.right
        z: 10
    }

    Connections {
        target: gameEngine

        onLevelReady: {
        }

        onLevelFinished: {
            continueBtn.opacity = 1;
        }
    }

    Flickable {
        id: boardFlickable
        //width: parent.width; height: parent.height
        //anchors.verticalCenter: parent.verticalCenter
        anchors.top: main.portrait ? gameHud.bottom : parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: main.portrait ? parent.right : gameHud.left

        contentWidth: boardLevel.width
        contentHeight: boardLevel.height
        maximumFlickVelocity: 500
        flickDeceleration: 1000
        clip: true

        Level {
            id: boardLevel
        }
    }

    Menu.Button {
        id: continueBtn
        anchors {bottom: parent.bottom; bottomMargin: 10; horizontalCenter: parent.horizontalCenter}
        width: parent.width / 2
        opacity: 0

        text: qsTr("Continue")
        disabled: false
        onClicked: {
            stateMachine.gameUIVisible = false;
            menuPanel.state = "levelSelection";
        }
    }

    states: [
        State {
            name: "enable"
            when: enabled
            PropertyChanges {
                target: gameBoard
                opacity: 1
            }
            PropertyChanges {
                target: continueBtn
                opacity: 0
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            properties: "opacity"
            duration: 500
        }
        NumberAnimation {
            properties: "scale"
            duration: 400
        }
    }
}
