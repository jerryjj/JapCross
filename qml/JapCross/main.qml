import QtQuick 1.0

import "Menu" 1.0 as Menu

AppWindow {
    id: main

    property bool portrait: true

    Component.onCompleted: {
        menuPanel.state = "showMain";
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
