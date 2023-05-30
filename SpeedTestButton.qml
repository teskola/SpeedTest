import QtQuick

Rectangle {
    id: button
    property color idleColor: "black"
    property color activatedColor: "black"
    property bool activated: false
    property bool keyPressed: false
    readonly property int originalLength: parent.width
    signal buttonClicked
    color: activated ? activatedColor : idleColor
    width: mouseArea.pressed || keyPressed ? 0.94 * originalLength : originalLength
    height: width
    radius: 0.5 * width
    anchors.centerIn: parent

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {            
            buttonClicked()
        }
    }
}
