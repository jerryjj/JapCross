import QtQuick 1.0

Item {
    id: gameBoard
    anchors.fill: parent

    opacity: 0

    //scale: gameEngine.zoomLevel
    scale: 1.0

    Image {
        id: gbBackground
        anchors.fill: parent
        source: "images/background.jpg"
        //fillMode: Image.PreserveAspectCrop
    }

    Flickable {
        scale: 1.0 //0.4
        id: boardFlickable
        width: parent.width; height: parent.height
        contentWidth: boardGrid.width
        contentHeight: boardGrid.height
        maximumFlickVelocity: 500
        flickDeceleration: 1000

        /*Item {
            id: boardGrid
            width: 400
            height: 500
            anchors.centerIn: parent
        }*/

        Grid {
            id: boardGrid
            columns: 10 //gameEngine.columnCount
            spacing: 0
            anchors.centerIn: parent

            Repeater {
                model: gameEngine.playableSquares
                PlayableSquare {}
            }
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
