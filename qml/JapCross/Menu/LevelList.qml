import QtQuick 1.0

Item {
    id: levelList
    width: parent.width; height: parent.height

    function getFormattedTime(pTime)
    {
        var minFirstDigits = Math.floor(pTime/600);
        var secFirstDigits = Math.floor(pTime/10);
        var formattedTime = minFirstDigits + "" +
            (Math.floor(pTime/60)-minFirstDigits*10) + ":" +
            secFirstDigits%6 + "" + (pTime-secFirstDigits*10);
        return formattedTime;
    }

    Component {
        id: lvlDelegate

        Item {
            width: levelList.width;
            height: 70

            Rectangle {
                //width: parent.width; height: 35
                anchors.fill: parent
                anchors.verticalCenter: parent.verticalCenter
                radius: 4
                //radius: 4; opacity: 0.8
                //smooth: true
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#fff" }
                    GradientStop { position: 1.0; color: "#562a7a" }
                }
            }

            Rectangle {
                id: thumbHolder
                width: 50; height: 50
                anchors {verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10}
                color: "#fff"
                border.width: 1
                border.color: "#abacad"
                radius: 2

                Image {
                    anchors.fill: parent
                    anchors.centerIn: parent
                    source: modelData.thumbnail
                    visible: modelData.thumbnail ? "visible" : ""
                }
            }

            Text {
                id: lvlName
                anchors { left: thumbHolder.right; leftMargin: 5; top: thumbHolder.top }
                text: modelData.grpName + ": " + modelData.lvlName
                font.pointSize: 14
                font.bold: true
                color: "#562a7a"
            }

            Text {
                id: lvlSize
                anchors { left: lvlName.right; leftMargin: 10; top: lvlName.top }
                text: "(" + modelData.cols + " x " + modelData.rows + ")"
                font.pointSize: 14
                font.bold: true
                color: "#562a7a"
            }

            Text {
                id: lblTimeSpent
                anchors { left: thumbHolder.right; leftMargin: 5; top: lvlName.bottom; topMargin: 5 }
                text: qsTr("Time spent") + ":"
                font.pointSize: 13
                font.bold: true
                color: "#fff"
                visible: modelData.timespent ? "visible" : ""
            }

            Text {
                id: lvlTimeSpent
                anchors { left: lblTimeSpent.right; leftMargin: 10; top: lblTimeSpent.top }
                text: getFormattedTime(modelData.timespent)
                font.pointSize: 13
                font.bold: false
                color: "#fff"
                visible: modelData.timespent ? "visible" : ""
            }

            Text {
                id: lvlAuthor
                anchors { right: parent.right; rightMargin: 10; bottom: parent.bottom; bottomMargin: 10 }
                text: qsTr("Author") + ": " + modelData.lvlAuthor
                font.pointSize: 12
                font.bold: false
                color: "#fff"
                visible: modelData.lvlAuthor ? "visible" : ""
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    startMenu.state = "hideAndLoadLevel";
                    gameBoard.enabled = false;
                    gameEngine.loadLevel(modelData.grp, modelData.lvl);
                }
            }
        }
    }

    ListView {
        id: lv
        anchors {fill: parent}

        model: levelEngine.availableLevels
        delegate: lvlDelegate
        clip: true
        cacheBuffer: 20
    }
}
