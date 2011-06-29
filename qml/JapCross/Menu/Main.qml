import QtQuick 1.0

Item {
    id: startMenu
    width: parent.width; height: parent.height
    opacity: 0

    Component.onCompleted: {
    }

    /*
    Image {
        id: menuBackground
        anchors.fill: parent
        source: "images/background.jpg"
        //fillMode: Image.PreserveAspectCrop
    }
    */

    Frame {
        id: startMenuFrame
        width: parent.width - 100
        height: (2*60) + 50
        anchors.verticalCenter: parent.verticalCenter

        x: 50

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
                    }
                }

                Button {
                    id: btnPlay
                    text: qsTr("Play")
                    disabled: false
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
            PropertyChanges {
                target: menuButton
                opacity: 0
            }
        },
        State {
            name: "hideAndLoadLevel"
            extend: "showMain"
            PropertyChanges {
                target: startMenu
                opacity: 0
            }
            PropertyChanges {
                target: menuButton
                opacity: 1
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
