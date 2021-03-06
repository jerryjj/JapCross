import QtQuick 1.0

Item {
    id: startMenu
    width: parent.width; height: parent.height
    opacity: 0

    Item {
        id: logoholder
        width: main.portrait ? 400 : 610
        height: main.portrait ? 75 : 116
        anchors { top: parent.top; topMargin: 50 } //; horizontalCenter: parent.horizontalCenter

        x: (parent.width / 2) - (logoholder.width / 2)

        Image {
            id: logo
            source: main.portrait ? "../images/logo-portrait.png" : "../images/logo.png"
        }
    }

    Item {
        id: startMenuFrame
        width: parent.width - 100
        height: (2*60) + 50

        anchors {top: logoholder.bottom; topMargin: 20} //horizontalCenter: parent.horizontalCenter;

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
                        startMenu.state = "instructions";
                    }
                }

                Button {
                    id: btnPlay
                    text: qsTr("Play")
                    disabled: false
                    onClicked: {
                        startMenu.state = "levelSelection";
                    }
                }
            }
        }
    }

    Item {
        id: levelSelectionFrame
        width: parent.width - 100; height: parent.height - 50
        anchors.verticalCenter: parent.verticalCenter
        x: parent.width + 100

        Row {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Column {
                width: parent.width; height: parent.height
                spacing: 10

                LevelList {
                    id: levelsList
                    height: parent.height - btnLsBackToMenu.height
                }

                Button {
                    id: btnLsBackToMenu
                    text: qsTr("Back to menu")
                    disabled: false
                    onClicked: {
                        startMenu.state = "showMain";
                    }
                }
            }
        }
    }

    Item {
        id: instructionsFrame
        width: parent.width - 100; height: parent.height - 50
        anchors.verticalCenter: parent.verticalCenter
        x: parent.width + 100

        Row {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Column {
                width: parent.width; height: parent.height
                spacing: 10

                Rectangle {
                    color: "#fff"
                    width: parent.width; height: parent.height - btnInstructionsBackToMenu.height
                    radius: 8

                    Flickable {
                        id: instructionsFlickable
                        width: parent.width - 10; height: parent.height - 10
                        anchors.centerIn: parent
                        maximumFlickVelocity: 500
                        flickDeceleration: 1000
                        contentHeight: instrTxt.height
                        clip: true

                        Text {
                            id: instrTxt
                            width: parent.width
                            color: "#000"
                            font.pointSize: 18
                            text: qsTr("game_instructions")
                            wrapMode: Text.WordWrap
                        }
                    }
                }

                Button {
                    id: btnInstructionsBackToMenu
                    text: qsTr("Back to menu")
                    disabled: false
                    onClicked: {
                        startMenu.state = "showMain";
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
            name: "instructions"
            extend: "showMain"
            PropertyChanges {
                target: logoholder
                x: -(startMenu.width + 50)
            }
            PropertyChanges {
                target: startMenuFrame
                x: -(startMenu.width + 50)
            }
            PropertyChanges {
                target: instructionsFrame
                x: 50
            }
        },
        State {
            name: "levelSelection"
            extend: "showMain"
            PropertyChanges {
                target: logoholder
                x: -(startMenu.width + 50)
            }
            PropertyChanges {
                target: startMenuFrame
                x: -(startMenu.width + 50)
            }
            PropertyChanges {
                target: levelSelectionFrame
                x: 50
            }
        },
        State {
            name: "hideAndLoadLevel"
            extend: "levelSelection"
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
        NumberAnimation {
            properties: "x"
            duration: 300
        }
    }
}
