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

        Menu {
            title: qsTr("&Shader")
            MenuItem {
                text: qsTr("&MIP")
                onTriggered: volView.setUseMIP(true)
            }
            MenuItem {
                text: qsTr("&Alpha")
                onTriggered: volView.setUseMIP(false)
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
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent

            Slider {
                id: slider1R
                x: 32
                y: 26
                width: 80
                height: 22
                value: 1
                stepSize: 0.01
                onValueChanged: volView.setRed1(slider1R.value)

            }

            Text {
                id: setRed
                x: 8
                y: 24
                color: "#ffffff"
                text: qsTr("R")
                font.pixelSize: 20
            }

            Text {
                id: setGreen
                x: 8
                y: 54
                color: "#ffffff"
                text: qsTr("G")
                font.pixelSize: 20
            }

            Slider {
                id: slider2R
                x: 131
                y: 26
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setRed2(slider2R.value)
            }

            Slider {
                id: slider3R
                x: 230
                y: 26
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setRed3(slider3R.value)
            }

            Slider {
                id: slider1G
                x: 32
                y: 56
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setGreen1(slider1G.value)
            }

            Slider {
                id: slider2G
                x: 131
                y: 56
                width: 80
                height: 22
                value: 1
                stepSize: 0.01
                onValueChanged: volView.setGreen2(slider2G.value)
            }

            Slider {
                id: slider3G
                x: 230
                y: 56
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setGreen3(slider3G.value)
            }

            Text {
                id: setBlue
                x: 8
                y: 84
                color: "#ffffff"
                text: qsTr("B")
                font.pixelSize: 20
            }

            Slider {
                id: slider1B
                x: 32
                y: 86
                width: 80
                height: 22
                value: 0.01
                stepSize: 0.01
                onValueChanged: volView.setBlue1(slider1B.value)
            }

            Slider {
                id: slider2B
                x: 131
                y: 86
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setBlue2(slider2B.value)
            }

            Slider {
                id: slider3B
                x: 230
                y: 86
                width: 80
                height: 22
                value: 1
                stepSize: 0.01
                onValueChanged: volView.setBlue3(slider3B.value)
            }

            Text {
                id: sampling
                x: 551
                y: 24
                color: "#ffffff"
                text: qsTr("Sampling")
                font.pixelSize: 20
            }

            Slider {
                id: samplingBar
                x: 354
                y: 26
                width: 179
                height: 22
                maximumValue: 0.1
                minimumValue: 0.001
                value: 0.05
                stepSize: 0.001

                onValueChanged: volView.setSampling(samplingBar.value)
            }
        }
    }

    FileDialog {
        id: loadDialog
        onAccepted: {
            volView.loadFile(loadDialog.fileUrl)
        }
    }
}
