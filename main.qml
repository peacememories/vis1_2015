import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import rendering 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: loadDialog.open()
            }

            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    VolumetricView {
        id: volView
        anchors.fill: parent
        viewDirection: camControl.direction

        CameraControl {
            id: camControl
            anchors.fill: parent
        }
    }

    Text {
        text: "Hi"
    }

    FileDialog {
        id: loadDialog
        onAccepted: {
            volView.loadFile(loadDialog.fileUrl)
        }
    }
}
