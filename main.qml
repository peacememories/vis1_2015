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
        viewPosition: camControl.position

        CameraControl {
            id: camControl
            anchors.fill: parent

            TextEdit {
                id: textRed
                x: 10
                y: 10
                width: 80
                height: 20
                color: "#ffffff"
                text: qsTr("R")
                font.pixelSize: 22
                onTextChanged: volView.setRed(textRed.getText(0,3) / 255)
            }
            TextEdit {
                id: textGreen
                x: 10
                y: 40
                width: 80
                height: 20
                color: "#ffffff"
                text: qsTr("G")
                font.pixelSize: 22
                onTextChanged: volView.setGreen(textGreen.getText(0,3) / 255)
            }
            TextEdit {
                id: textBlue
                x: 10
                y: 70
                width: 80
                height: 20
                color: "#ffffff"
                text: qsTr("B")
                font.pixelSize: 22
                onTextChanged: volView.setBlue(textBlue.getText(0,3) / 255)
            }
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
