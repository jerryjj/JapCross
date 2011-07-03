import QtQuick 1.0

Item {
    id: level

    property int innerMargin: 10

    width: (leftHeader.width * 2) + pictureGrid.width + (innerMargin * 2)
    height: (topHeader.height * 2) + pictureGrid.height + (innerMargin * 2)

    Connections {
        target: gameEngine

        onLevelLoading: {
            bgRect.opacity = 0;
            topHeader.opacity = 1;
            bottomHeader.opacity = 1;
            leftHeader.opacity = 1;
            rightHeader.opacity = 1;
        }

        onLevelFinished: {
            bgRect.opacity = 1;
            topHeader.opacity = 0.1;
            bottomHeader.opacity = 0.1;
            leftHeader.opacity = 0.1;
            rightHeader.opacity = 0.1;
        }
    }

    Item {
        anchors {fill: parent; topMargin: level.innerMargin; leftMargin: level.innerMargin; bottomMargin: level.innerMargin; rightMargin: level.innerMargin}

        Row {
            id: topHeader
            anchors {left: pictureGrid.left; top: parent.top}

            Repeater {
                id: topHeaderRepeater
                model: gameEngine.level.tbHeaders
                TopColumn {
                    hpos: "top"
                }
            }
        }

        Grid {
            id: leftHeader
            anchors {left: parent.left; top: pictureGrid.top}
            columns: 1

            Repeater {
                model: gameEngine.level.lrHeaders
                SideRow {
                    hpos: "left"
                }
            }
        }

        Rectangle {
            id: bgRect
            color: "#fff"
            width: pictureGrid.width; height: pictureGrid.height
            anchors {left: pictureGrid.left; top: pictureGrid.top}
            opacity: 0
        }

        Grid {
            id: pictureGrid
            rows: gameEngine.level.rows
            columns: gameEngine.level.cols
            spacing: 0
            anchors {left: leftHeader.right; top: topHeader.bottom}

            Repeater {
                model: gameEngine.level.playableCells
                PlayableCell {}
            }
        }

        Row {
            id: bottomHeader
            anchors {left: pictureGrid.left; top: pictureGrid.bottom}

            Repeater {
                model: gameEngine.level.tbHeaders
                TopColumn {
                    hpos: "bottom"
                }
            }
        }

        Grid {
            id: rightHeader
            anchors {left: pictureGrid.right; top: pictureGrid.top}
            columns: 1

            Repeater {
                model: gameEngine.level.lrHeaders
                SideRow {
                    hpos: "right"
                }
            }
        }
    }

}
