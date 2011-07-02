import QtQuick 1.0

Item {
    id: startMenu
    width: parent.width; height: parent.height
    opacity: 0

    Connections {
        target: gameEngine

        onLevelReady: {
            btnPlay.disabled = false;
        }
    }

    Item {
        id: logoholder
        width: 610; height: 116
        anchors { top: parent.top; topMargin: 50; horizontalCenter: parent.horizontalCenter }

        Image {
            id: logo
            source: "../images/logo.png"
        }
    }

    Frame {
        id: startMenuFrame
        width: parent.width - 100
        height: (2*60) + 50
        anchors {horizontalCenter: parent.horizontalCenter; top: logoholder.bottom; topMargin: 20}

        opacity: 0
        scale: 0

        Row {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Column {
                width: parent.width
                spacing: 10

                Button {
                    id: btnInstructions
                    text: qsTr("Instructions")
                    disabled: false
                    onClicked: {
                        //startMenu.state = "instructions";
                        gameEngine.loadLevel(1);
                    }
                }

                Button {
                    id: btnPlay
                    text: qsTr("Play")
                    disabled: true
                    onClicked: {
                        //startMenu.state = "levelSelection";
                        startMenu.state = "hideAndLoadLevel";
                        gameBoard.enabled = true;
                        stateMachine.gameUIVisible = true;
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "showMain"
            PropertyChanges {
                target: startMenu
                opacity: 1
            }
            PropertyChanges {
                target: startMenuFrame
                opacity: 1
                scale: 1.0
            }
        },
        State {
            name: "hideAndLoadLevel"
            extend: "showMain"
            PropertyChanges {
                target: startMenu
                opacity: 0
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            properties: "opacity, scale"
            duration: 500
        }
    }
}
