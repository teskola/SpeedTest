import QtQuick

Rectangle {
    id: button
    property color idleColor: "black"
    property color activatedColor: "black"
    property bool activated: false
    property bool keyPressed: false
    readonly property int originalWidth: parent.width
    readonly property int originalHeight: parent.height    
    signal buttonClicked
    color: activated ? activatedColor : idleColor
    width: originalWidth
    height: originalHeight
    radius: 0.5 * width
    anchors.centerIn: parent
    states:
        State {
            name: "pressed"
            when: mouseArea.pressed || keyPressed
            PropertyChanges {
                target: button
                width: 0.94 * originalWidth
                height: 0.94 * originalHeight
            }
        }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {            
            buttonClicked()
        }
    }
}
