import QtQuick 1.0

import "Menu" 1.0 as Menu

Item {
    id: main

    Component.onCompleted: {
        menuPanel.state = "showMain";
    }

    Image {
        id: background
        anchors.fill: parent
        source: "images/background.png"
        //fillMode: Image.PreserveAspectCrop
    }

    Item {
        id: menuButton
        width: 60
        height: 60
        anchors { top: parent.top; left: parent.left; leftMargin: 5 }

        z: 100
        opacity: (stateMachine.gameUIVisible ? 1 : 0)

        Image {
            source: "images/menu.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                gameBoard.enabled = false;
                menuPanel.state = "showMain";
                stateMachine.gameUIVisible = false;
            }
        }

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 400
            }
        }
    }

    Item {
        id: gameUI
        anchors.fill: parent
        opacity: 0
        state: (stateMachine.gameUIVisible ? "visible" : "")

        GameBoard {
            id: gameBoard
            enabled: false
        }

        states: [
            State {
                name: "visible"
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
