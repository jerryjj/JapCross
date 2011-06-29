import QtQuick 1.0

Item {
    id: level

    Grid {
        id: topGrid
        columns: 10 //gameEngine.columnCount
        //rows: gameEngine.rowCount
        spacing: 0
        anchors {left: leftGrid.right; top: parent.top}

        Repeater {
            model: gameEngine.topColumns
            NumberColumn {
                cpos:  "top"
            }
        }
    }

    Grid {
        id: leftGrid
        columns: 10 //gameEngine.columnCount
        //rows: gameEngine.rowCount
        spacing: 0
        anchors {left: parent.left; top: topGrid.bottom}

        Repeater {
            model: gameEngine.sideColumns
            NumberColumn {
                cpos:  "left"
            }
        }
    }

    Grid {
        id: pictureGrid
        columns: 10 //gameEngine.columnCount
        //rows: gameEngine.rowCount
        spacing: 0
        anchors {left: leftGrid.right; top: topGrid.bottom}

        Repeater {
            model: gameEngine.playableSquares
            PlayableSquare {}
        }
    }

    Grid {
        id: bottomGrid
        columns: 10 //gameEngine.columnCount
        //rows: gameEngine.rowCount
        spacing: 0
        anchors {left: leftGrid.right; top: pictureGrid.bottom}

        Repeater {
            model: gameEngine.topColumns
            NumberColumn {
                cpos:  "bottom"
            }
        }
    }

    Grid {
        id: rightGrid
        columns: 10 //gameEngine.columnCount
        //rows: gameEngine.rowCount
        spacing: 0
        anchors {left: pictureGrid.right; top: topGrid.bottom}

        Repeater {
            model: gameEngine.sideColumns
            NumberColumn {
                cpos:  "right"
            }
        }
    }
}
