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

    Item {
        id: flipable
        anchors.fill: parent
        opacity: 1

        property bool flipped: modelData.inUse
        property bool cellActive: modelData.active

        Rectangle {
            anchors.fill: parent
            color:  "#F5F2E3"

            Rectangle {
                anchors.fill: parent
                border.width: 1

                BorderImage {
                    anchors.fill: parent
                    source: "images/cell-border-darker-t.png"
                    border {top: 1}
                    visible: (modelData.row == 1) ? "visible" : ""
                }

                BorderImage {
                    anchors.fill: parent
                    source: "images/cell-border-darker-l.png"
                    border {left: 1}
                    visible: (modelData.col == 1) ? "visible" : ""
                }

                BorderImage {
                    anchors.fill: parent
                    source: "images/cell-border-darker-l.png"
                    border {left: 1}
                    visible: ((modelData.col % 5) == 1) ? "visible" : ""
                }

                BorderImage {
                    anchors.fill: parent
                    source: "images/cell-border-darker-r.png"
                    visible: (modelData.col == gameEngine.level.cols) ? "visible" : ""
                }

                BorderImage {
                    anchors.fill: parent
                    source: "images/cell-border-darker-b.png"
                    border {bottom: 0}
                    visible: (modelData.row == gameEngine.level.rows) ? "visible" : ""
                }

                BorderImage {
                    anchors.fill: parent
                    source: "images/cell-border-darker-b.png"
                    border {bottom: 0}
                    visible: (modelData.row % 5 == 0 && modelData.row != gameEngine.level.rows) ? "visible" : ""
                }
            }

            Text {
                anchors.centerIn:  parent
                color: "#333333"
                text: "X"
                font.pointSize: 20
                visible: flipable.flipped && !flipable.cellActive
            }

            Item {
                width: ((modelData.col % 5) == 1) ? parent.width - 4 : parent.width - 3
                height: ((modelData.row % 5) == 0) ? parent.height - 4 : parent.height - 3
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: ((modelData.col % 5) == 1) ? 3 : 2

                Rectangle {
                    anchors.fill: parent
                    color: "#5E5E5E"
                    visible: flipable.flipped && flipable.cellActive
                }
            }
        }

    }
}
