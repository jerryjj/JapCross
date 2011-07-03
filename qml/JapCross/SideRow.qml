import QtQuick 1.0

Item {
    id: sideRow

    property string hpos: "left"
    property int sridx: index

    width: (modelData.itemCount() * 25)
    height: 40

    anchors.right: hpos == "left" ? (parent ? parent.right : undefined) : undefined
    anchors.left: hpos == "right" ? (parent ? parent.left : undefined) : undefined

    Grid {
        rows: 1
        columns: modelData.itemCount()
        spacing: 0

        Repeater {
            model: modelData.items
            NumberColumn {
                cpos: hpos
                idx: sridx
            }
        }
    }

}
