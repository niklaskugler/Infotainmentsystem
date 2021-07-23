import QtQml 2.12
import QtQuick 2.12
import QtPositioning 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// Implementierung des Eingabefenster für das Koordinaten-Geocoding

Item {
    property string title;
    property variant coordinate
    signal showPlace(variant coordinate)
    signal closeForm()

    property alias clearButton: clearButton
    property alias goButton: goButton
    property alias longitude: longitude
    property alias latitude: latitude
    property alias cancelButton: cancelButton
    property alias tabTitle: tabTitle


    anchors.rightMargin: 0
    anchors.leftMargin: 150

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
            text: qsTr("Reverse Geocode")
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
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            rowSpacing: 10
            rows: 1
            columns: 2
            anchors.fill: parent

            // define input field for entering coordinates
            Label {
                id: label2
                text: qsTr("Latitude")
            }

            TextField {
                id: latitude
                Layout.fillWidth: true
            }

            Label {
                id: label3
                text: qsTr("Longitude")
            }

            TextField {
                id: longitude
                Layout.fillWidth: true
                placeholderText: qsTr("")
            }

            RowLayout {
                id: rowLayout1
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight

                Button {
                    id: goButton
                    text: qsTr("Proceed")
                    onClicked: {
                            var coordinate = QtPositioning.coordinate(parseFloat(latitude.text),
                                                                              parseFloat(longitude.text));
                            if (coordinate.isValid) {
                                showPlace(coordinate)
                            }
                            closeForm()
                        }
                }

                Button {
                    id: clearButton
                    text: qsTr("Clear")
                    onClicked: {
                            latitude.text = ""
                            longitude.text = ""
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
                    latitude.text = "" + coordinate.latitude
                    longitude.text = "" + coordinate.longitude
                    if (title.length != 0) {
                        tabTitle.text = title;
                    }
                }

            }
            Item {
                Layout.fillHeight: true
                Layout.columnSpan: 2
            }
        }
    }
}

