import QtQuick 1.1
import com.meego 1.0

Window {
    id: win
    property bool windowactive: true

    function updateActive() {
        if (platformWindow.active) {
            win.windowactive = true;
        } else {
            win.windowactive = false;
        }
    }

    Connections {
        target: platformWindow

        onActiveChanged: updateActive()
    }
}
