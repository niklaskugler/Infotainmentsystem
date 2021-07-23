import QtQuick 2.12
import QtQml 2.12
import QtPositioning 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// Implementierung des Eingabefenster für das Adress-Geocoding

Item {
    property variant address
    signal showPlace(variant address)
    signal closeForm()


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
            text: qsTr("Geocode")
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

            // definition of the input fields
            Label {
                id: label2
                text: qsTr("Street")
            }

            TextField {
                id: street
                Layout.fillWidth: true
            }

            Label {
                id: label3
                text: qsTr("City")
            }

            TextField {
                id: city
                Layout.fillWidth: true
            }

            Label {
                id: label5
                text: qsTr("Country")
            }

            TextField {
                id: country
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
                        // fill out the Address element
                        address.street = street.text
                        address.city = city.text

                        address.country = country.text
                        var addressString ="";
                        if(street.text)
                            addressString += street.text + ','
                        if(city.text)
                            addressString += city.text + ','
                        if(country.text)
                            addressString += country.text

                        //signal is generated here with input parameters
                        // showplce function call which shows the geocoding request
                        showPlace(addressString)
                        closeForm()
                    }

                }

                Button {
                    id: clearButton
                    text: qsTr("Clear")
                    onClicked: {
                        street.text = ""
                        city.text = ""
                        country.text = ""
                    }
                }

                Button {
                    id: cancelButton
                    text: qsTr("Cancel")
                    onClicked: {
                        //close form signal is generated here with input parameters
                        closeForm()
                    }
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.columnSpan: 2
            }
        }
        Component.onCompleted: {
            street.text = address.street
            city.text = address.city
            country.text = address.country
        }
    }

}




