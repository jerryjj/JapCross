import QtQuick 1.0

Item {
    id: playableSquare

    width: 40; height: 40

    MouseArea {
        anchors.fill: parent
        onClicked: {
            gameEngine.markPlayableCell(index);
        }
    }

    Connections {
        target: gameEngine

        onLevelFinished: {
            if (!modelData.inUse) {
                flipable.cellActive = false;
                flipable.opacity = 0.1;
            } else {
                if (!flipable.cellActive) {
                    flipable.opacity = 0.1;
                } else {
                    flipable.cellActive = true;
                }
            }
            flipable.flipped = true;
        }
    }

    Flipable {
        id: flipable
        anchors.fill: parent
        state: "front"
        opacity: 1

        property bool flipped: modelData.inUse ? true : false
        property int xAxis: 1
        property int yAxis: 0
        property int angle: 180

        property bool cellActive: modelData.active

        front: Rectangle {
            anchors.fill: parent
            color:  "#F5F2E3"

            Rectangle {
                anchors.fill: parent
                border.width: 1
            }

        }

        back: Rectangle {
            anchors.fill: parent
            color: "#F5F2E3" //modelData.active ? "#5E5E5E" : "#F5F2E3"

            Rectangle {
                anchors.fill: parent
                border.width: 1

                /*Rectangle {
                    anchors.fill:  parent
                    color: "lightgrey"
                    visible: !modelData.active
                }*/
                Text {
                    anchors.centerIn:  parent
                    color: "#333333"
                    text: "X"
                    font.pointSize: 20
                }

                Rectangle {
                    anchors.fill: parent
                    color: "#5E5E5E"
                    visible: flipable.cellActive
                }
            }
        }

        transform: Rotation {
            id: rotation; origin.x: flipable.width / 2; origin.y: flipable.height / 2
            axis.x: flipable.xAxis; axis.y: flipable.yAxis; axis.z: 0
        }

        states: State {
            name: "back"; when: flipable.flipped
            PropertyChanges { target: rotation; angle: flipable.angle }
        }

        transitions: [
            Transition {
                ParallelAnimation {
                    NumberAnimation { target: rotation; properties: "angle"; duration: 500 }
                    SequentialAnimation {
                        NumberAnimation { target: flipable; property: "scale"; to: 0.9; duration: 300 }
                        NumberAnimation { target: flipable; property: "scale"; to: 1.0; duration: 300 }
                    }
                }
            },
            Transition {
                NumberAnimation { properties: "opacity"; duration: 600 }
            }

        ]
    }
}