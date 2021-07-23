import QtQuick 2.4
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Item {
    width: 210
    height: 210
    property string str: "22 °C"
    property string color_backround: "#4ddb0d0d"
    property string color_border: "#c30d0d"


    function change_driver_temp(temp, c1, c2) {
        str = temp +" °C"
        color_backround = c1
        color_border = c2
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 210
        height: 210
        border.color: color_border
        border.width: 5
        radius: width*0.5
        gradient: Gradient {
            GradientStop {
                position: 0
                color: color_backround
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
            text: qsTr(str)
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
    }
}
