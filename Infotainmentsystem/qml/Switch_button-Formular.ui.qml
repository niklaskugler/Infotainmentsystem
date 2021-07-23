import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles.Desktop 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Imagine 2.3
import QtQuick.Controls.Universal 2.0

Item {
    width: 106
    height: 40

    Rectangle {
        id: rectangle
        width: 106
        height: 40
        color: "#00ffffff"
        border.color: "#00000000"

        Switch {
            id: switch1
            x: 0
            y: 0
            width: 106
            height: 40
            visible: true
            checkable: true
            layer.enabled: false
            scale: 1
            checked: false

            indicator: Rectangle {
                    implicitWidth: 70
                    implicitHeight: 26
                    x: switch1.leftPadding
                    y: switch1.height / 2 - height / 2
                    radius: 13
                    color: switch1.checked ? "#0088ff" : "#ffffff"
                    border.color: switch1.checked ? "#0088ff" : "#cccccc"

                    Rectangle {
                                x: switch1.checked ? parent.width - width : 0
                                y: -5
                                width: 35
                                height: 35
                                radius: 20
                                color: switch1.down ? "#cccccc" : "#ffffff"
                                border.color: switch1.checked ? (switch1.down ? "#17a81a" : "#21be2b") : "#999999"
                            }
            }
        }
    }
}
