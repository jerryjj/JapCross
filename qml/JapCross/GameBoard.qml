import QtQuick 1.0

Item {
    id: gameBoard
    anchors.fill: parent

    opacity: 0

    //scale: gameEngine.zoomLevel
    scale: 1.0

    /*Image {
        id: gbBackground
        anchors.fill: parent
        source: "images/background.png"
        //fillMode: Image.PreserveAspectCrop
    }*/

    clip: true

    Flickable {
        id: boardFlickable
        //width: parent.width - 150; height:  parent.height
        //anchors.verticalCenter: parent.verticalCenter
        anchors.fill:  parent
        contentWidth: boardLevel.width
        contentHeight: boardLevel.height
        maximumFlickVelocity: 500
        flickDeceleration: 1000

        Level {
            id: boardLevel            
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
