import QtQml 2.12
import QtQuick 2.12
import QtPositioning 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtLocation 5.12

// Implementierung des Eingabefenster für das Adress-Routing

Item {
    property variant fromAddress;
    property variant toAddress;
    property string fromAddressString: ""
    property string toAddressString: ""
    signal showMessage(string topic, string message)
    signal decodeAddresses(string fromAddress, string toAddress)
    signal showRoute(variant startCoordinate,variant endCoordinate)
    signal closeForm()

    property alias fromStreet: fromStreet
    property alias fromCountry: fromCountry
    property alias toStreet: toStreet
    property alias toCity: toCity
    property alias toCountry: toCountry
    property alias fromCity: fromCity
    property alias goButton: goButton
    property alias clearButton: clearButton
    property alias cancelButton: cancelButton


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
            text: qsTr("Route Address")
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
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                Layout.columnSpan : 2
            }

            Label {
                id: label2
                text: qsTr("Street")
            }

            TextField {
                id: fromStreet
                Layout.fillWidth: true
            }

            Label {
                id: label3
                text: qsTr("City")
            }

            TextField {
                id: fromCity
                Layout.fillWidth: true
            }

            Label {
                id: label7
                text: qsTr("Country")
            }

            TextField {
                id: fromCountry
                Layout.fillWidth: true
            }

            Label {
                id: label6
                text: qsTr("To")
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                Layout.columnSpan: 2
            }

            Label {
                id: label4
                text: qsTr("Street")
            }

            TextField {
                id: toStreet
                Layout.fillWidth: true
            }

            Label {
                id: label5
                text: qsTr("City")
            }

            TextField {
                id: toCity
                Layout.fillWidth: true
            }

            Label {
                id: label8
                text: qsTr("Country")
            }

            TextField {
                id: toCountry
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
                        fromAddress.country =  fromCountry.text
                        fromAddress.street = fromStreet.text
                        fromAddress.city =  fromCity.text
                        toAddress.country = toCountry.text
                        toAddress.street = toStreet.text
                        toAddress.city = toCity.text

                        toAddressString ="";
                        if(toStreet.text)
                            toAddressString += toStreet.text + ','
                        if(toCity.text)
                            toAddressString += toCity.text + ','
                        if(toCountry.text)
                            toAddressString += toCountry.text

                        fromAddressString ="";
                        if(fromStreet.text)
                            fromAddressString += fromStreet.text + ','
                        if(fromCity.text)
                            fromAddressString += fromCity.text + ','
                        if(fromCountry.text)
                            fromAddressString += fromCountry.text

                        decodeAddresses(fromAddressString, toAddressString)
                        closeForm()
                    }
                }

                Button {
                    id: clearButton
                    text: qsTr("Clear")
                    onClicked: {
                        fromStreet.text = ""
                        fromCity.text = ""
                        fromCountry.text = ""
                        toStreet.text = ""
                        toCity.text = ""
                        toCountry.text = ""
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
                    fromStreet.text  = fromAddress.street
                    fromCity.text =  fromAddress.city
                    fromCountry.text = fromAddress.country
                    toStreet.text = toAddress.street
                    toCity.text = toAddress.city
                    toCountry.text = toAddress.country
                }

            }

            Item {
                Layout.fillHeight: true
                Layout.columnSpan: 2
            }
        }
    }

}
