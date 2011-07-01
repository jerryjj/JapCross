import QtQuick 1.0

Item {
    id: column

    property int idx: 0
    property string cpos: "top"

    width: ((cpos == "top" || cpos == "bottom") ? 40 : (modelData.inUse ? 25 : 0))
    height: ((cpos == "top" || cpos == "bottom") ? (modelData.inUse ? 25 : 0) : 40)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (cpos == "top" || cpos == "bottom") gameEngine.markTopColumnSquare(idx, index);
            else if (cpos == "left" || cpos == "right") gameEngine.markSideColumnSquare(idx, index);
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#E7E3CE"
        visible: modelData.inUse

        Rectangle {
            anchors.fill: parent
            border.width: 1

            Text {
                anchors.centerIn:  parent
                color: modelData.marked ? "#cccccc" : "#333333"
                text: modelData.value
                font.pointSize: 20
            }
        }
    }
}
