import QtQuick 1.0

Item {
    id: container

    property string text: ""
    property bool disabled: false
    property bool pressed: false
    signal clicked

    // Suitable default size
    width: parent.width
    height: 50

    function getLabelModel(lbl) {
        var letters = lbl.split("");
        var model = Qt.createQmlObject('import Qt 4.7; ListModel {}', container);

        for (var i = 0; i < letters.length; i++) {
            model.append({letter: letters[i]});
        }

        return model;
    }

    Rectangle {
        id: numberHolder
        width: 50; height: parent.height
        anchors.left: parent.left
        border.color: "#abacad"
        border.width: 1

        color: "#562a7a"

        Text {
            font.family: "nokia"
            font.pointSize: 26
            smooth: true
            anchors.centerIn: parent
            color: "#fff"
            //color: container.disabled ? "#ccc" : "#333"
            //text: container.text.length
            text: "!"
        }
    }

    Rectangle {
        id: normal
        width: parent.width - numberHolder.width; height: parent.height
        x: numberHolder.x + numberHolder.width + 1
        border.color: "#abacad"
        border.width: 1

        color: container.pressed ? "#562a7a" : "#fff"

        Text {
            font.family: "nokia"
            font.pointSize: 26
            font.bold: true
            smooth: true
            color: container.disabled ? "#ccc" : (container.pressed ? "#fff" : "#562a7a")
            anchors.centerIn: parent
            text: container.text
        }

        /*Row {
            Repeater {
                model: getLabelModel(container.text)
                delegate: Rectangle {
                    width: numberHolder.width; height: numberHolder.height
                    border.color: "#abacad"
                    border.width: 1
                    color: "#fff"

                    Text {
                        font.family: "nokia"
                        font.pointSize: 26
                        font.bold: true
                        smooth: true
                        color: container.disabled ? "#ccc" : "#562a7a"
                        anchors.centerIn: parent
                        text: modelData
                    }
                }
            }
        }*/
    }

    /*Rectangle {
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
    }*/


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
        PropertyChanges { target: container; pressed: true }
        //PropertyChanges { target: pressed; opacity: 1 }
    }
    ]
    transitions: Transition {
        NumberAnimation { properties: "opacity"; duration:100 }
    }
}
