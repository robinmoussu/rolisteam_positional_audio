import QtQuick 2.9
import QtQuick.Window 2.2
import io.qt.examples.mumbleplugin 1.0

Window {
    visible: true
    id: root

    Image {
        id: map
        visible: true
        source: "qrc:///ressources/tavern.png"
    }

    MumblePlugin {
        id: mumblePlugin
    }

    signal adventurerPosition(double x, double y)

    Image {
        id: adventurer
        visible: true
        source: "qrc:///ressources/adventurer.png"
        x: (map.width - adventurer.width)/2
        y: (map.height - adventurer.height)/2

        MouseArea {
            anchors.fill: parent
            drag.target: adventurer
            drag.minimumX: 0
            drag.maximumX: map.width - adventurer.width
            drag.minimumY: 0
            drag.maximumY: map.height - adventurer.height
            hoverEnabled: true
            cursorShape: this.pressed? Qt.ClosedHandCursor : Qt.OpenHandCursor

            onReleased: {
                console.log("position: ", adventurer.x + adventurer.width/2 - map.width/2, ":", adventurer.y + adventurer.height/2 - map.width/2)
                root.adventurerPosition(adventurer.x + adventurer.width/2 - map.width/2, adventurer.y + adventurer.height/2 - map.width/2)
                cursorShape: Qt.OpenHandCursor
            }
        }
    }

    width: map.width
    height: map.height
    title: qsTr("Tavern")
}
