import QtQuick 1.0

Item {
    width: main.portrait ? parent.width : 100
    height: main.portrait ? 70 : parent.height

    function getFormattedTime(pTime)
    {
        var minFirstDigits = Math.floor(pTime/600);
        var secFirstDigits = Math.floor(pTime/10);
        var formattedTime = minFirstDigits + "" +
            (Math.floor(pTime/60)-minFirstDigits*10) + ":" +
            secFirstDigits%6 + "" + (pTime-secFirstDigits*10);
        return formattedTime;
    }

    Rectangle {
        color: "#fff"
        anchors.fill: parent
    }

    Item {
        id: menuButton
        width: 50; height: 40
        anchors.top: parent.top
        anchors.topMargin: main.portrait ? (parent.height / 2 - height / 2) : 10
        anchors.left: parent.left
        anchors.leftMargin: main.portrait ? 10 : (parent.width / 2 - width / 2)

        Image {
            source: "images/menu.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                gameEngine.saveGameState();
                gameBoard.enabled = false;
                menuPanel.state = "levelSelection";
                stateMachine.gameUIVisible = false;
            }
        }
    }

    Text {
        id: timespent
        anchors.top: main.portrait ? parent.top : menuButton.bottom
        anchors.topMargin: main.portrait ? (parent.height / 2 - height / 2) : 10
        anchors.left: main.portrait ? menuButton.right : parent.left
        anchors.leftMargin: main.portrait ? 10 : (parent.width / 2 - width / 2)

        font.family: "nokia"
        font.pointSize: 16

        text: getFormattedTime(gameEngine.level.timespent)
    }

    Text {
        id: levelName
        anchors {left: timespent.right; leftMargin: 10; verticalCenter: parent.verticalCenter}
        visible: main.portrait ? "visible" : ""

        font.family: "nokia"
        font.pointSize: 18
        color: "#562a7a"

        text: gameEngine.level.name
    }

    Item {
        id: clearBtn
        width: 50; height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: main.portrait ? (parent.height / 2 - height / 2) : 10
        anchors.right: parent.right
        anchors.rightMargin: main.portrait ? 10 : (parent.width / 2 - width / 2)

        visible: gameEngine.level.levelFinished ? "visible" : ""

        Image {
            source: "images/clear.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                gameEngine.clearGameState();
            }
        }
    }

    transitions: Transition {
        NumberAnimation {
            properties: "x,y"
            duration: 400
        }
    }
}
