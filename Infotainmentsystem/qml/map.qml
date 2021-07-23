import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12

// Implementierung der Map des Navigatinssystem
// Implementierung der Routing und Geocoding Funktionalität
// Basierend auf der von Qt bereitgesellten MinimalMap (Implementierungsbeispiel)
// https://doc.qt.io/qt-5/qtlocation-minimal-map-example.html

Rectangle {
    width: 640
    height: 480
    visible: true

    Item {
        id: root

        //initiale Koordinaten für Routing auf Basis von Koordinaten

        //initiale Startadresse - vordefinierte Startposition ist aktuelle Position - HTWG Konstanz
        property variant fromCoordinate: QtPositioning.coordinate(47.66700571686962, 9.170516638506747) // HTWG
        property variant toCoordinate: QtPositioning.coordinate(47.682333815979185, 9.21127671880107) // Fähre

        property variant startCoordinate: QtPositioning.coordinate()
        property variant endCoordinate: QtPositioning.coordinate()

        // initiale Adressen für adressbasiertes Routing

        // initiale Startadresse - vordefinierte Startposition ist aktuelle Position - HTWG Konstanz
        Address {
            id :fromAddress
            street: "Alfred-Wachtel-Straße 5"
            city: "Konstanz"
            country: "Germany"
        }

        //initial final Address - already predefined for demonstration purpose
        Address {
            id: toAddress
            street: "Gustav-Schwab-Straße 11"
            city: "Konstanz"
            country: "Germany"
        }

        // maps plugin that uses open street maps
        Plugin{
            id: mapPlugin
            name: "osm"
        }

        // RouteMode instantiation that uses query to be executed by the user
        RouteModel {
            id: routeModel
            plugin: mapPlugin
            query: RouteQuery {
                id: routeQuery
            }

        }

        // used for address translation from address string to coordinates
        GeocodeModel {
            id: geocodeModel
            plugin: mapPlugin
            onStatusChanged: {
                if ((status == GeocodeModel.Ready) || (status == GeocodeModel.Error))
                    map.geocodeFinished()
            }

            onLocationsChanged:
            {
                console.log("Location change called with count = ", count)
                if (count >= 1) {
                    map.center.latitude = get(0).coordinate.latitude
                    map.center.longitude = get(0).coordinate.longitude
                }
            }
        }

        // used for address translation from address string to coordinates in Route by Address and Route by coordinates
        GeocodeModel {
            id: geocodeModel2
            plugin: mapPlugin
            property bool start: true
            property string endAddress: ""

            onStatusChanged: {
                // error handling geocoding
                if ((status == GeocodeModel.Ready) || (status == GeocodeModel.Error))
                    map.geocodeFinished()
            }

            onLocationsChanged:
            {
                console.log("Location change2 called with count = ", count)

                if (count >= 1 && start == true) {
                    console.log("start Coordinates Initiated")
                    root.startCoordinate.latitude = get(0).coordinate.latitude
                    root.startCoordinate.longitude = get(0).coordinate.longitude

                    start = false
                    query = endAddress
                    update()
                }

                if (count >= 1 && start == false) {
                    console.log("End Coordinates Initiated")
                    root.endCoordinate.latitude = get(0).coordinate.latitude
                    root.endCoordinate.longitude = get(0).coordinate.longitude
                    // Computation of the Route
                    map.calculateCoordinateRoute(root.startCoordinate, root.endCoordinate)
                }
            }
        }

        //Used to display and interact with maps
        Map{
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            // vordefinierte Zoom-Level
            zoomLevel: 15
            gesture.enabled: true
            // initiale Startcoordinaten HTWG Konstanz --> Positionierung der map beim Starten des Navi
            center: QtPositioning.coordinate(47.66759325360248, 9.171904989523949)
            signal geocodeFinished()

            function calculateCoordinateRoute(startCoordinate, endCoordinate)
            {
                //! [routerequest0]
                // clear away any old data in the query
                routeQuery.clearWaypoints();

                // add the start and end coordinates as waypoints on the route
                routeQuery.addWaypoint(startCoordinate)
                routeQuery.addWaypoint(endCoordinate)
                routeQuery.travelModes = RouteQuery.CarTravel
                routeQuery.routeOptimizations = RouteQuery.FastestRoute


                //! [routerequest0 feature weight]
                for (var i=0; i<9; i++) {
                    routeQuery.setFeatureWeight(i, 0)
                }

                routeModel.update();

                // center the map on the start coord
                map.center = startCoordinate;
                //! [routerequest2]
            }


            function geocode(fromAddress)
            {
                //! [geocode1]
                // send the geocode request
                geocodeModel.query = fromAddress
                geocodeModel.update()
                //! [geocode1]
            }

            function geocodeRoute(fromAddress, toAddress) {
                //! [geocode1]
                // send the geocode request
                geocodeModel2.start = true
                geocodeModel2.endAddress = toAddress
                geocodeModel2.query = fromAddress
                geocodeModel2.update()

                console.log("in geocode route = ", fromAddress,  " ", toAddress)
                //! [geocode1]
            }

            onGeocodeFinished: {
                // error handling geocoding
                if (geocodeModel.status == GeocodeModel.Ready) {
                    if (geocodeModel.count == 0) {
                        console.log("Geocode Error: Count = 0")
                    }
                    else if (geocodeModel.count > 1) {
                        console.log("Ambiguous geocode ", geocodeModel.count, " results found for the given address, please specify location")
                    } else {
                        console.log("Geocode Error: Unsuccessful geocode")
                    }
                }
                else if (geocodeModel.status == GeocodeModel.Error) {
                    console.log("Geocode Error: Unsuccessful geocode")
                }
            }

            //Route visuals settings
            MapItemView {
                model: routeModel
                delegate: MapRoute {
                    route: routeData
                    line.color: "blue"
                    line.width: 5
                    smooth: true
                }
            }

        }

        //top menu bar
        SideMenu {
            id: sideMenu

            //jede Schaltfläche mit ihrem individuellen Ereignis
            //jede Schaltfläche öffnet eine qml-Komponente, die für verschiedene Zwecke verwendet wird
            geocodeButton.onClicked:  {
                stackView.pop({root, immediate: true})
                stackView.push("qrc:/qml/Geocode.qml",{"address": fromAddress}, {operation:  StackView.ReplaceTransition})
                stackView.currentItem.showPlace.connect(map.geocode)
                stackView.currentItem.closeForm.connect(stackView.closeForm)
            }
            revGeocodeButton.onClicked:  {
                stackView.pop({root, immediate: true})
                stackView.push("qrc:/qml/ReverseGeocode.qml",{"coordinate": root.fromCoordinate},  {operation:  StackView.ReplaceTransition})
                stackView.currentItem.showPlace.connect(map.geocode)
                stackView.currentItem.closeForm.connect(stackView.closeForm)
            }
            routeByAddressButton.onClicked: {
                stackView.pop({root, immediate: true})
                stackView.push("qrc:/qml/RouteAddress.qml",
                               {/*"plugin": map.plugin,*/ "toAddress": toAddress, "fromAddress": fromAddress},
                               {operation:  StackView.ReplaceTransition})
                stackView.currentItem.decodeAddresses.connect(map.geocodeRoute)
                stackView.currentItem.showRoute.connect(map.calculateCoordinateRoute)
                stackView.currentItem.closeForm.connect(stackView.closeForm)
            }
            routeByCoordinatesButton.onClicked: {
                stackView.pop({root, immediate: true})
                stackView.push("qrc:/qml/RouteCoordinate.qml",
                               { "toCoordinate": root.toCoordinate, "fromCoordinate": root.fromCoordinate},
                               {operation:  StackView.ReplaceTransition})
                stackView.currentItem.showRoute.connect(map.calculateCoordinateRoute)
                stackView.currentItem.closeForm.connect(stackView.closeForm)
            }
        }

    }

    // Navigationselement für die StackView
    StackView {
        id: stackView
        anchors.fill: parent
        focus: true
        initialItem: root

        function closeForm()
        {
            pop()
        }

    }


}

