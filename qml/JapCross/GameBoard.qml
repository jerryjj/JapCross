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

    Flickable {
        scale: 1.0 //0.4
        id: boardFlickable
        width: parent.width; height: parent.height
        contentWidth: boardLevel.width + 100
        contentHeight: boardLevel.height + 100
        maximumFlickVelocity: 500
        flickDeceleration: 1000

        Level {
            id: boardLevel
            //anchors {topMargin: 20; leftMargin: 20}
            anchors.centerIn: parent
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
