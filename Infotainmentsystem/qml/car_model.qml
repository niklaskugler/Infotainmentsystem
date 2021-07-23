import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick3D.Helpers 1.14
import QtQuick3D.Materials 1.14
import QtQuick.Window 2.14


Item {
    width: 600
    height: 400

    property double rot_angle: 0.0

    Timer {
            interval: 20; running: true; repeat: true
            onTriggered: rot_angle = rot_angle+0.5
    }

   /*
    function change_rot_angle() {
        rot_angle = rot_angle + 0.5
    }
    */

    Rectangle {
        id: rect
        width: 600
        height: 400
        color: "#00ffffff"
        View3D {
            id: view3D
            x: 0
            y: 0
            width: 600
            height: 400
            SceneEnvironment {
                id: sceneEnvironment
                antialiasingMode: SceneEnvironment.MSAA
                antialiasingQuality: SceneEnvironment.High
            }

            Node {
                id: scene
                scale.z: 100
                scale.y: 100
                scale.x: 100
                DirectionalLight {
                    id: directionalLight
                    x: 6.218
                    y: 7.381
                    brightness: 102
                    scale.z: 0.1
                    scale.y: 0.1
                    scale.x: 0.1
                    z: 12.06717
                    eulerRotation.z: -5.30128
                    eulerRotation.y: 27.10118
                    eulerRotation.x: -10.44653
                }

                PerspectiveCamera {
                    id: camera
                    x: -0.025
                    y: 1.395
                    scale.z: 0.1
                    scale.y: 0.1
                    scale.x: 0.1
                    eulerRotation.z: -0.46317
                    eulerRotation.y: 2.61104
                    eulerRotation.x: -19.77239
                    z: 3.62219
                }
                Node{
                    eulerRotation.y: rot_angle
                    eulerRotation.z: 0
                    eulerRotation.x: 0
                Model {
                        id: plate_R_Bolt_001
                        source: "qrc:/Car_Model/meshes/plate_R_Bolt_001.mesh"

                        DefaultMaterial {
                            id: ______301_material
                            diffuseColor: "#be0e0e"
                        }
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: aMG1___014
                        source: "qrc:/Car_Model/meshes/aMG1___014.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: wheel_LR___033
                        source: "qrc:/Car_Model/meshes/wheel_LR___033.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: brake_F___034
                        source: "qrc:/Car_Model/meshes/brake_F___034.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: brake_R___035
                        source: "qrc:/Car_Model/meshes/brake_R___035.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: emblem___015
                        source: "qrc:/Car_Model/meshes/emblem___015.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: light_F___002
                        source: "qrc:/Car_Model/meshes/light_F___002.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: wheel_RF___042
                        source: "qrc:/Car_Model/meshes/wheel_RF___042.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: wheel_RR___043
                        source: "qrc:/Car_Model/meshes/wheel_RR___043.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: wheel_cap_F___003
                        source: "qrc:/Car_Model/meshes/wheel_cap_F___003.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: wheel_cap_R___012
                        source: "qrc:/Car_Model/meshes/wheel_cap_R___012.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: wheel_LF___032
                        source: "qrc:/Car_Model/meshes/wheel_LF___032.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: mesh____005
                        source: "qrc:/Car_Model/meshes/mesh____005.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: light1____003
                        source: "qrc:/Car_Model/meshes/light1____003.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: light_clear_F____015
                        source: "qrc:/Car_Model/meshes/light_clear_F____015.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: window_R____045
                        source: "qrc:/Car_Model/meshes/window_R____045.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: windowframe_S____031
                        source: "qrc:/Car_Model/meshes/windowframe_S____031.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: light_R____088
                        source: "qrc:/Car_Model/meshes/light_R____088.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: spoiler____020
                        source: "qrc:/Car_Model/meshes/spoiler____020.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body____021
                        source: "qrc:/Car_Model/meshes/body____021.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: window_F____044
                        source: "qrc:/Car_Model/meshes/window_F____044.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: spoiler2____025
                        source: "qrc:/Car_Model/meshes/spoiler2____025.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: diffuser____026
                        source: "qrc:/Car_Model/meshes/diffuser____026.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: window_S____032
                        source: "qrc:/Car_Model/meshes/window_S____032.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: exhaust____034
                        source: "qrc:/Car_Model/meshes/exhaust____034.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: chassis_____042
                        source: "qrc:/Car_Model/meshes/chassis_____042.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: caliper_F____019
                        source: "qrc:/Car_Model/meshes/caliper_F____019.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: roof____072
                        source: "qrc:/Car_Model/meshes/roof____072.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: windowframe_R____087
                        source: "qrc:/Car_Model/meshes/windowframe_R____087.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: light_R2____099
                        source: "qrc:/Car_Model/meshes/light_R2____099.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: caliper_R____093
                        source: "qrc:/Car_Model/meshes/caliper_R____093.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: lED_R____095
                        source: "qrc:/Car_Model/meshes/lED_R____095.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: light_clear_R____118
                        source: "qrc:/Car_Model/meshes/light_clear_R____118.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: lED_red____101
                        source: "qrc:/Car_Model/meshes/lED_red____101.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: emblem_R____094
                        source: "qrc:/Car_Model/meshes/emblem_R____094.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: light_red_R____107
                        source: "qrc:/Car_Model/meshes/light_red_R____107.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: plate_F_Bolt_002
                        source: "qrc:/Car_Model/meshes/plate_F_Bolt_002.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: v8_BITURBO____124
                        source: "qrc:/Car_Model/meshes/v8_BITURBO____124.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: lED_F_______
                        source: "qrc:/Car_Model/meshes/lED_F_______.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: mirror_clear____123
                        source: "qrc:/Car_Model/meshes/mirror_clear____123.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: mirror_LED____129
                        source: "qrc:/Car_Model/meshes/mirror_LED____129.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: mirror_001____132
                        source: "qrc:/Car_Model/meshes/mirror_001____132.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: doorhandle____133
                        source: "qrc:/Car_Model/meshes/doorhandle____133.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: emblem_F____008
                        source: "qrc:/Car_Model/meshes/emblem_F____008.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: aMG_logo_F____141
                        source: "qrc:/Car_Model/meshes/aMG_logo_F____141.mesh"
                        materials: [
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: aMG_logo_R____145
                        source: "qrc:/Car_Model/meshes/aMG_logo_R____145.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: tyreLF_g_Tyre_LF
                        source: "qrc:/Car_Model/meshes/tyreLF_g_Tyre_LF.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: tyreLR_g_Tyre_LR
                        source: "qrc:/Car_Model/meshes/tyreLR_g_Tyre_LR.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: tyreRF_g_Tyre_RF
                        source: "qrc:/Car_Model/meshes/tyreRF_g_Tyre_RF.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: tyreRR_g_Tyre_RR
                        source: "qrc:/Car_Model/meshes/tyreRR_g_Tyre_RR.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: wiper3____051
                        source: "qrc:/Car_Model/meshes/wiper3____051.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: wiper1___
                        source: "qrc:/Car_Model/meshes/wiper1___.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: wiper2____060
                        source: "qrc:/Car_Model/meshes/wiper2____060.mesh"
                        materials: [
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material,
                            ______301_material
                        ]
                    }

                    Model {
                        id: windowframe_F____080
                        source: "qrc:/Car_Model/meshes/windowframe_F____080.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_001____001
                        source: "qrc:/Car_Model/meshes/body_001____001.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_002____002
                        source: "qrc:/Car_Model/meshes/body_002____002.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_003____004
                        source: "qrc:/Car_Model/meshes/body_003____004.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_004____006
                        source: "qrc:/Car_Model/meshes/body_004____006.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_005____007
                        source: "qrc:/Car_Model/meshes/body_005____007.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_006____008
                        source: "qrc:/Car_Model/meshes/body_006____008.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_007____009
                        source: "qrc:/Car_Model/meshes/body_007____009.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_008____010
                        source: "qrc:/Car_Model/meshes/body_008____010.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_009____011
                        source: "qrc:/Car_Model/meshes/body_009____011.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_010____012
                        source: "qrc:/Car_Model/meshes/body_010____012.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_011____013
                        source: "qrc:/Car_Model/meshes/body_011____013.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_012____014
                        source: "qrc:/Car_Model/meshes/body_012____014.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_013____016
                        source: "qrc:/Car_Model/meshes/body_013____016.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_014____017
                        source: "qrc:/Car_Model/meshes/body_014____017.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_015____018
                        source: "qrc:/Car_Model/meshes/body_015____018.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_016____022
                        source: "qrc:/Car_Model/meshes/body_016____022.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_017____023
                        source: "qrc:/Car_Model/meshes/body_017____023.mesh"
                        materials: [
                            ______301_material
                        ]
                    }

                    Model {
                        id: body_018____024
                        source: "qrc:/Car_Model/meshes/body_018____024.mesh"
                        materials: [
                            ______301_material
                        ]
                    }
                    }
            }
            environment: sceneEnvironment
        }


    }
}

