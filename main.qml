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
                id: useMIP
                text: qsTr("&MIP")
                onTriggered: volView.setShader(1), threshold.visible = false, thresholdBar.visible = false, sampling.visible = true, samplingBar.visible = true, slider2B.visible = false, slider2G.visible = false, slider2R.visible = false, slider3B.visible = false, slider3G.visible = false, slider3R.visible = false
            }
            MenuItem {
                id: useAlpha
                text: qsTr("&Alpha")
                onTriggered: volView.setShader(2), threshold.visible = false, thresholdBar.visible = false, sampling.visible = false, samplingBar.visible = false, slider2B.visible = true, slider2G.visible = true, slider2R.visible = true, slider3B.visible = true, slider3G.visible = true, slider3R.visible = true
            }
            MenuItem {
                id: useFirsthit
                text: qsTr("&First Hit")
                onTriggered: volView.setShader(3), threshold.visible = true, thresholdBar.visible = true, sampling.visible = true, samplingBar.visible = true, slider2B.visible = false, slider2G.visible = false, slider2R.visible = false, slider3B.visible = false, slider3G.visible = false, slider3R.visible = false
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
                visible: true
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
                visible: true
            }

            Text {
                id: setGreen
                x: 8
                y: 54
                color: "#ffffff"
                text: qsTr("G")
                font.pixelSize: 20
                visible: true
            }

            Slider {
                id: slider2R
                x: 131
                y: 26
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setRed2(slider2R.value)
                visible: false
            }

            Slider {
                id: slider3R
                x: 230
                y: 26
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setRed3(slider3R.value)
                visible: false
            }

            Slider {
                id: slider1G
                x: 32
                y: 56
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setGreen1(slider1G.value)
                visible: true
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
                visible: false
            }

            Slider {
                id: slider3G
                x: 230
                y: 56
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setGreen3(slider3G.value)
                visible: false
            }

            Text {
                id: setBlue
                x: 8
                y: 84
                color: "#ffffff"
                text: qsTr("B")
                font.pixelSize: 20
                visible: true
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
                visible: true
            }

            Slider {
                id: slider2B
                x: 131
                y: 86
                width: 80
                height: 22
                stepSize: 0.01
                onValueChanged: volView.setBlue2(slider2B.value)
                visible: false
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
                visible: false
            }

            Text {
                id: sampling
                x: 551
                y: 24
                color: "#ffffff"
                text: qsTr("Sampling")
                font.pixelSize: 20
                visible: true
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
                visible: true
                onValueChanged: volView.setSampling(samplingBar.value)
            }

            Slider {
                id: thresholdBar
                x: 354
                y: 56
                width: 179
                height: 22
                value: 0.05
                stepSize: 0.001
                minimumValue: 0.001
                maximumValue: 1
                onValueChanged: volView.setTh(thresholdBar.value)
                visible: false
            }

            Text {
                id: threshold
                x: 548
                y: 54
                color: "#ffffff"
                text: qsTr("Threshold")
                font.pixelSize: 20
                visible: false
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
