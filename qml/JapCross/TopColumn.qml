import QtQuick 1.0

Column {
    id: topColumn

    property string hpos: "top"
    property int tcidx: index

    width: 40

    anchors.bottom: hpos == "top" ? parent.bottom : undefined
    anchors.top: hpos == "bottom" ? parent.top : undefined

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
