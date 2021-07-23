import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11

RowLayout {
    id: sideMenu
    property alias geocodeButton: geocodeButton
    property alias revGeocodeButton: revGeocodeButton
    property alias routeByAddressButton: routeByAddressButton
    property alias routeByCoordinatesButton: routeByCoordinatesButton
    Button {
        id: menuBtn
        text: qsTr("")
        checked: false
        display: AbstractButton.IconOnly
        checkable: true

        icon {
            color: "transparent"
            source: "qrc:/Images/menu.png"
        }
    }

    RowLayout {
        width: sideMenu.implicitWidth
        height: sideMenu.implicitHeight
        visible: menuBtn.checked

        Button {
            id: geocodeButton
            Layout.fillHeight: true
            //Layout.fillWidth: true
            display: AbstractButton.IconOnly

            icon {
                color: "transparent"
                source: "qrc:/Images/position.png"
            }
        }

        Button {
            id: revGeocodeButton
            //Layout.fillWidth: true
            Layout.fillHeight: true
            display: AbstractButton.IconOnly

            icon {
                color: "transparent"
                source: "qrc:/Images/position_coordinates.png"
            }
        }

        Button {
            id: routeByAddressButton
            //Layout.fillWidth: true
            Layout.fillHeight: true
            display: AbstractButton.IconOnly

            icon {
                color: "transparent"
                source: "qrc:/Images/navigation.png"
            }
        }

        Button {
            id: routeByCoordinatesButton
            //Layout.fillWidth: true
            Layout.fillHeight: true
            display: AbstractButton.IconOnly

            icon {
                color: "transparent"
                source: "qrc:/Images/navigationByCoordinates.jpg"
            }
        }
    }
}

