import QtQuick 1.0

Item {
    width: main.portrait ? parent.width : 100
    height: main.portrait ? 70 : parent.height

    Rectangle {
        color: "#fff"
        anchors.fill: parent
    }

    Item {
        id: menuButton
        width: 50; height: 40
        anchors.top: parent.top
        anchors.topMargin: main.portrait ? 15 : 10
        anchors.left: parent.left
        anchors.leftMargin: main.portrait ? 10 : 25

        Image {
            source: "images/menu.png"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                gameBoard.enabled = false;
                menuPanel.state = "showMain";
                stateMachine.gameUIVisible = false;
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
