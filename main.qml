import QtQuick
import QtCore
import QtQuick.Layouts
import QtQuick.Controls.Material 2.3
import SpeedTest 1.0

ApplicationWindow {
    id: window
    visible: true
    visibility: "FullScreen"
    title: qsTr("Speedtest")    

    SpeedTest {
       id: speedTest
    }    

    Rectangle {

        id: background
        width: parent.width
        height: parent.height
        color: "black"
        focus: true
        Keys.onPressed: (event) => {
                            switch (event.key) {

                                case Qt.Key_A:
                                redButton.state = "pressed"
                                redButton.buttonClicked()
                                break;

                                case Qt.Key_S:
                                blueButton.state = "pressed"
                                blueButton.buttonClicked()
                                break;

                                case Qt.Key_D:
                                orangeButton.state = "pressed"
                                orangeButton.buttonClicked()
                                break;

                                case Qt.Key_F:
                                yellowButton.state = "pressed"
                                yellowButton.buttonClicked()
                                break;
                            }
                        }
        Keys.onReleased: (event) => {
                             switch (event.key) {
                                 case Qt.Key_A:
                                 redButton.state = "released"
                                 break;

                                 case Qt.Key_S:
                                 blueButton.state = "released"
                                 break;

                                 case Qt.Key_D:
                                 orangeButton.state = "released"
                                 break;

                                 case Qt.Key_F:
                                 yellowButton.state = "released"
                                 break;
                             }
                         }

        Dialog {
            id: dialog
            visible: speedTest.gameEnded
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            closePolicy: Popup.NoAutoClose
            dim: false
            title: speedTest.count > 0 ? qsTr("Points: ") + speedTest.count : ""

            ColumnLayout {
                id: dialogLayout
                anchors.fill: parent

                Text {
                    text: "(" + speedTest.interval + "ms)"
                    visible: speedTest.count > 0
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: qsTr("New record!")
                    visible: speedTest.count > speedTest.record
                    Layout.alignment: Qt.AlignHCenter
                }

                Button {
                    text: qsTr("New game")
                    highlighted: true
                    Layout.fillWidth: true
                    onClicked: speedTest.startGame();
                    Shortcut {
                        sequence: "Space"
                        onActivated: speedTest.gameEnded && speedTest.startGame();
                    }
                }
                Button {
                    text: qsTr("Quit")
                    Layout.fillWidth: true
                    onClicked: Qt.callLater(Qt.quit());
                    Shortcut {
                        sequences: [StandardKey.Quit, "Esc"]
                        onActivated: Qt.callLater(Qt.quit());
                    }
                }
            }
        }

        RowLayout {
            id: buttonLayout
            anchors.fill: parent

            Rectangle {
                id: red
                color: background.color
                Layout.fillWidth: true
                Layout.preferredHeight: width                
                SpeedTestButton {
                    id: redButton
                    idleColor: "#330000"
                    activatedColor: "#FF0000"
                    activated: speedTest.red_activated
                    onButtonClicked: speedTest.buttonPressed(0)

                }
            }
            Rectangle {
                id: blue
                Layout.fillWidth: true
                Layout.preferredHeight: width
                color: background.color
                SpeedTestButton {
                    id: blueButton
                    idleColor: "#000033"
                    activatedColor: "#0000FF"
                    activated: speedTest.blue_activated
                    onButtonClicked: speedTest.buttonPressed(1)
                }

            }
            Rectangle {
                id: orange
                Layout.fillWidth: true
                Layout.preferredHeight: width
                color: background.color
                SpeedTestButton {
                    id: orangeButton
                    idleColor: "#331900"
                    activatedColor: "#FF8000"
                    activated: speedTest.orange_activated
                    onButtonClicked: speedTest.buttonPressed(2)
                }
            }
            Rectangle {
                id: yellow
                Layout.fillWidth: true
                Layout.preferredHeight: width
                color: background.color
                SpeedTestButton {
                    id: yellowButton
                    idleColor: "#333300"
                    activatedColor: "#FFFF00"
                    activated: speedTest.yellow_activated
                    onButtonClicked: speedTest.buttonPressed(3)
                }
            }
        }

        Text {
            id: pointsText
            text: speedTest.count
            color: speedTest.count > speedTest.record ? "green" : "red"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }

        Text {
            id: recordText
            text: speedTest.record
            color: "red"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 10
            anchors.rightMargin: 10
        }


    }
}
