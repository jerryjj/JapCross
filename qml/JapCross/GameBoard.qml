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

    GameHud {
        id: gameHud
        anchors.top: parent.top
        anchors.right: parent.right
        z: 10
    }

    Connections {
        target: gameEngine

        onLevelReady: {
            //boardFlickable.loadLevel();
            boardLevel.visible = true;
        }
    }

    Flickable {
        id: boardFlickable
        //width: parent.width; height: parent.height
        //anchors.verticalCenter: parent.verticalCenter
        anchors.top: main.portrait ? gameHud.bottom : parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: main.portrait ? parent.right : gameHud.left

        contentWidth: boardLevel.width
        contentHeight: boardLevel.height
        maximumFlickVelocity: 500
        flickDeceleration: 1000
        clip: true

        Level {
            id: boardLevel
            visible: false
        }

        function loadLevel() {
//            var lvl = Qt.createQmlObject('import QtQuick 1.0; Level { id: boardLevel }', boardFlickable, "boardLevel");

//            var component = Qt.createComponent("Level.qml");
//            component.createObject(boardFlickable.contentItem);
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
