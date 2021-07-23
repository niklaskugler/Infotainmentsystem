import QtQml 2.12
import QtQuick 2.12
import QtPositioning 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


// Implementierung des Eingabefenster für das Koordinaten-Routing

Item {
    property variant toCoordinate
    property variant fromCoordinate
    signal showRoute(variant startCoordinate,variant endCoordinate)
    signal closeForm()


    property alias fromLatitude: fromLatitude
    property alias fromLongitude: fromLongitude
    property alias toLatitude: toLatitude
    property alias toLongitude: toLongitude
    property alias clearButton: clearButton
    property alias goButton: goButton
    property alias cancelButton: cancelButton


    anchors.rightMargin: 0
    anchors.leftMargin: 150
    anchors.left: parent.left
    anchors.right: parent.right

    Rectangle {
        id: tabRectangle
        y: 20
        height: tabTitle.height * 2
        color: "#46a2da"
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            id: tabTitle
            color: "#ffffff"
            text: qsTr("Route Coordinates")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: item2
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tabRectangle.bottom

        GridLayout {
            id: gridLayout3
            rowSpacing: 10
            rows: 1
            columns: 2
            anchors.fill: parent

            Label {
                id: label1
                text: qsTr("From")
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                Layout.columnSpan : 2
            }

            Label {
                id: label2
                text: qsTr("Latitude")
            }

            TextField {
                id: fromLatitude
                Layout.fillWidth: true
            }

            Label {
                id: label3
                text: qsTr("Longitude")
            }

            TextField {
                id: fromLongitude
                Layout.fillWidth: true
            }

            Label {
                id: label6
                text: qsTr("To")
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                Layout.columnSpan: 2
            }

            Label {
                id: label4
                text: qsTr("Latitude")
            }

            TextField {
                id: toLatitude
                Layout.fillWidth: true
            }

            Label {
                id: label5
                text: qsTr("Longitude")
            }

            TextField {
                id: toLongitude
                Layout.fillWidth: true
            }

            RowLayout {
                id: rowLayout1
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight
                Button {
                    id: goButton
                    text: qsTr("Proceed")
                    onClicked: {
                        var startCoordinate = QtPositioning.coordinate(parseFloat(fromLatitude.text),
                                                                       parseFloat(fromLongitude.text));
                        var endCoordinate = QtPositioning.coordinate(parseFloat(toLatitude.text),
                                                                     parseFloat(toLongitude.text));
                        if (startCoordinate.isValid && endCoordinate.isValid) {
                            goButton.enabled = false;
                            showRoute(startCoordinate,endCoordinate)
                        }
                        closeForm()
                    }
                }

                Button {
                    id: clearButton
                    text: qsTr("Clear")
                    onClicked: {
                        fromLatitude.text = ""
                        fromLongitude.text = ""
                        toLatitude.text = ""
                        toLongitude.text  = ""
                    }
                }

                Button {
                    id: cancelButton
                    text: qsTr("Cancel")
                    onClicked: {
                        closeForm()
                    }
                }


                Component.onCompleted: {
                    fromLatitude.text = "" + fromCoordinate.latitude
                    fromLongitude.text = "" + fromCoordinate.longitude
                    toLatitude.text = "" + toCoordinate.latitude
                    toLongitude.text = "" + toCoordinate.longitude
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.columnSpan: 2
            }
        }
    }
}
