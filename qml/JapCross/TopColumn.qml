import QtQuick 1.0

Column {
    id: topColumn

    property string hpos: "top"
    property int tcidx: index

    width: 40

    anchors.bottom: hpos == "top" ? (parent ? parent.bottom : undefined) : undefined
    anchors.top: hpos == "bottom" ? (parent ? parent.top : undefined) : undefined

    Grid {
        columns: 1
        spacing: 0

        Repeater {
            model: modelData.items
            NumberColumn {
                cpos: hpos
                idx: tcidx
            }
        }
    }
}
