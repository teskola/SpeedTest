import QtQuick 2.15
import QtQuick.Window 2.15
import TimosComponent 1.0

Window {
    width: 1280
    height: 480
    visible: true
    title: qsTr("Speedtest")

    SpeedTest {
       id: speedTest
    }

    Rectangle {

        width: parent.width
        height: parent.height
        color: "black"
        focus: true
        Keys.onPressed: (event) => {
                            switch (event.key) {
                                case Qt.Key_A:
                                state = "red_pressed";
                                speedTest.buttonPressed(0);
                                break;
                                case Qt.Key_S:
                                state = "blue_pressed";
                                speedTest.buttonPressed(1);
                                break;
                                case Qt.Key_D:
                                state = "orange_pressed";
                                speedTest.buttonPressed(2);
                                break;
                                case Qt.Key_F:
                                state = "yellow_pressed";
                                speedTest.buttonPressed(3);
                                break;
                                case Qt.Key_Space:
                                speedTest.startGame();
                                break;
                            }
                        }
        Keys.onReleased: (event) => { state = "" };

        states: [

            State {
                name: "red_pressed"
                PropertyChanges {
                    target: red
                    y: 175
                    x: 15
                    width: 290
                    height: 290
                }
            },
            State {
                name: "blue_pressed"
                PropertyChanges {
                    target: blue
                    y: 175
                    x: 335
                    width: 290
                    height: 290
                }
            },
            State {
                name: "orange_pressed"
                PropertyChanges {
                    target: orange
                    y: 175
                    x: 655
                    width: 290
                    height: 290
                }
            },
            State {
                name: "yellow_pressed"
                PropertyChanges {
                    target: yellow
                    y: 175
                    x: 975
                    width: 290
                    height: 290
                }
            }
        ]

        Rectangle {
            id: header
            x: 0
            y: 0
            width: parent.width
            height: 160
            color: "lightblue"
            Text {
                id: countText
                anchors.centerIn: parent
                text: speedTest.count
            }
        }

        Rectangle {
            id: red
            x:10
            y:170
            width: 300
            height: 300
            color: speedTest.color_red
            radius: 0.5 * width

        }
        Rectangle {
            id: blue
            x:330
            y:170
            width: 300
            height: 300
            color: speedTest.color_blue
            radius: 0.5 * width

        }
        Rectangle {
            id: orange
            x:650
            y:170
            width: 300
            height: 300
            color: speedTest.color_orange
            radius: 0.5 * width



        }
        Rectangle {
            id: yellow
            x:970
            y:170
            width: 300
            height: 300
            color: speedTest.color_yellow
            radius: 0.5 * width

        }

    }







}
