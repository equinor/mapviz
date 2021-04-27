/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.0
import QtDataVisualization 1.2
import QtQuick.Dialogs 1.0
import "."



Item {
    id: mainview
    width: 1280
    height: 720
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: "/"
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            Qt.quit()
        }
        Component.onCompleted: visible = false
    }

    function removeSurf (name) {
        if (surfaceLayers.seriesList.length>0){
            for (let i = 0; i < surfaceLayers.seriesList.length; i++) {
                if (surfaceLayers.seriesList[i].objectName === name) {
                    surfaceLayers.removeSeries(surfaceLayers.seriesList[i])
                    return
                }
            }
        }
        // iterate over itemsContainer children to find and return the object with matching string objectName (not id)

    }
    function addSurf (name) {
        if (surfContainer.resources.length>0){
            for (let i = 0; i < surfContainer.resources.length; i++) {
                if (surfContainer.resources[i].objectName === name) {
                    surfaceLayers.addSeries(surfContainer.resources[i])
                    return
                }
            }
        }
        // iterate over itemsContainer children to find and return the object with matching string objectName (not id)

    }
    property real fontSize: 12
    Data {
        id: surfaceData
    }
    Item {
        id: surfContainer

        Surface3DSeries {
            objectName: "layer_1"
            flatShadingEnabled: false
            drawMode: Surface3DSeries.DrawSurface
            baseGradient: layerOneGradient
            ItemModelSurfaceDataProxy {
                itemModel: surfaceData.modelName
                rowRole: "longitude"
                columnRole: "latitude"
                yPosRole: "height"
            }
            //! [4]
            visible: true
            //! [4]
        }
        Surface3DSeries {
            objectName: "layer_2"
            baseGradient: layerThreeGradient
            HeightMapSurfaceDataProxy {
                heightMapFile: ":/heightmaps/layer_2.png"
            }
            flatShadingEnabled: false
            drawMode: Surface3DSeries.DrawSurface
            visible: true // bind to checkbox state
        }
        Surface3DSeries {
            objectName: "layer_3"
            baseGradient: layerThreeGradient
            HeightMapSurfaceDataProxy {
                heightMapFile: ":/heightmaps/layer_3.png"
            }
            flatShadingEnabled: false
            drawMode: Surface3DSeries.DrawSurface
            visible: true // bind to checkbox state
        }

    }

    Item {

        id: surfaceView
        width: mainview.width - buttonLayout.width
        height: mainview.height
        anchors.right: mainview.right;

        //! [0]
        ColorGradient {
            id: layerOneGradient
            ColorGradientStop { position: 0.0; color: "black" }
            ColorGradientStop { position: 0.31; color: "tan" }
            ColorGradientStop { position: 0.62; color: "green" }
            ColorGradientStop { position: 0.80; color: "darkslategray" }
            ColorGradientStop { position: 1.0; color: "white" }
        }

        ColorGradient {
            id: layerTwoGradient
            ColorGradientStop { position: 0.315; color: "blue" }
            ColorGradientStop { position: 0.33; color: "white" }
        }

        ColorGradient {
            id: layerThreeGradient
            ColorGradientStop { position: 0.0; color: "red" }
            ColorGradientStop { position: 0.15; color: "black" }
        }
        //! [0]

        Surface3D {
            id: surfaceLayers
            objectName: layers
            width: surfaceView.width
            height: surfaceView.height
            theme: Theme3D {
                type: Theme3D.ThemeEbony
                font.pointSize: 35
                colorStyle: Theme3D.ColorStyleRangeGradient
            }
            shadowQuality: AbstractGraph3D.ShadowQualityNone
            selectionMode: AbstractGraph3D.SelectionItem
            aspectRatio: 1
            scene.activeCamera.cameraPreset: Camera3D.CameraPresetIsometricLeft
            axisY.min: 20
            axisY.max: 200
            axisX.segmentCount: 5
            axisX.subSegmentCount: 2
            axisX.labelFormat: "%i"
            axisZ.segmentCount: 5
            axisZ.subSegmentCount: 2
            axisZ.labelFormat: "%i"
            axisY.segmentCount: 5
            axisY.subSegmentCount: 2
            axisY.labelFormat: "%i"

            //! [1]
            //! [2]


            //! [1]
        }
    }

    ColumnLayout {
        id: buttonLayout
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: 0

        //! [3]
        GroupBox {
            Layout.fillWidth: true
            Column {
                spacing: 10

                Label {
                    font.pointSize: fontSize
                    font.bold: true
                    text: "Layer Selection"
                }

                CheckBox {
                    id: layerOneToggle
                    checked: true
                    text: "Show Ground Layer"

                }

            }
        }
        //! [3]

        //! [5]
        Button {
            text: "open"
            onClicked: fileDialog.open();
        }

        ComboBox {
            id: comboboxId
            width: parent.width / 2
            height: 50
            displayText: "Grids"
            model: surflist
            delegate: Item {
                width: parent.width
                height: 50
                Row {
                    spacing: 5
                    anchors.fill: parent
                    anchors.margins: 5
                    CheckBox {
                        id: cahc
                        height: parent.height
                        width: height
                        checked: false
                        onCheckedChanged: {

                            if(checked)
                            {
                                addSurf(name);
                            }
                            else if (!checked){
                                removeSurf(name);
                            }

                        }
                    }
                    Label {
                        text: name
                        width: parent.width - cahc.width
                        height: parent.height
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                    }
                }
            }

        }

        ListModel {
            id:surflist
                        ListElement { name: "layer_1"; file: ":/heightmaps/layer_3.png"; ischecked: true }
                        ListElement { name: "layer_2"; file: ":/heightmaps/layer_2.png"; ischecked: false }
                        ListElement { name: "layer_3"; file: ":/heightmaps/layer_3.png"; ischecked: true }
                    }



        //! [5]

        //! [6]


    }
}
