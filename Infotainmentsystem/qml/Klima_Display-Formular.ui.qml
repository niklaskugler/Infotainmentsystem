import QtQuick 2.4
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Item {
    width: 210
    height: 210

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 210
        height: 210
        border.color: "#404040"
        border.width: 5
        radius: width*0.5
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#4d404040"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        Text {
            id: text1
            x: 38
            y: 67
            width: 135
            height: 77
            color: "#ffffff"
            text: qsTr("24 °C")
            font.pixelSize: 46
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            style: Text.Raised
            font.weight: Font.Normal
            font.family: "Arial"
            font.bold: true
            minimumPointSize: 12
            minimumPixelSize: 12

        }
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: 210
        height: 210
        color: "#00ffffff"
        border.color: "#00000000"
    }
}
