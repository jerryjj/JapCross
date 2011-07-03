import QtQuick 1.0

Item {
    id: container

    property string text: ""
    property bool disabled: false
    signal clicked

    // Suitable default size
    width: parent.width
    height: 60

    Rectangle {
        id: numberHolder
        width: 60; height: parent.height
        anchors.left: parent.left
        border.color: "#abacad"
        border.width: 1

        color: "#fff"

        Text {
            font.family: "nokia"
            font.pointSize: 26
            smooth: true
            color: {
                if (container.disabled)
                    "#ccc"
                else
                    "#333"
            }
            anchors.centerIn: parent
            text: container.text.length
        }
    }

    Rectangle {
        id: normal
        width: parent.width - numberHolder.width; height: parent.height
        x: numberHolder.x + numberHolder.width + 1
        border.color: "#abacad"
        border.width: 1

        color: "#fff"

        Text {
            font.family: "nokia"
            font.pointSize: 26
            font.bold: true
            smooth: true
            color: {
                if (container.disabled)
                    "#ccc"
                else
                    "#562a7a"
            }
            anchors.centerIn: parent
            text: container.text
        }
    }

    Rectangle {
        id: pressed
        width: parent.width - numberHolder.width; height: parent.height
        x: numberHolder.x + numberHolder.width + 1
        border.color: "#abacad"
        border.width: 1
        opacity: 0

        color: "#fff"

        Text {
            font.family: "nokia"
            font.pointSize: 26
            font.bold: true
            smooth: true
            color: "#fff"
            anchors.centerIn: parent
            text: container.text
        }

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#fff" }
            GradientStop { position: 1.0; color: "#562a7a" }
        }
    }


    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!container.disabled)
                container.clicked()
        }
        onPressed: {
            if (!container.disabled)
                container.state = "Pressed"
        }
        onReleased: {
            if (!container.disabled)
                container.state = ""
        }
    }

    states: [
    State {
        name: "Pressed"
        PropertyChanges { target: pressed; opacity: 1 }
    }
    ]
    transitions: Transition {
        NumberAnimation { properties: "opacity"; duration:100 }
    }
}
