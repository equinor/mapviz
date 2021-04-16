import QtQuick 2.1
import QtDataVisualization 1.2

Item {
    id: newbutton

    property alias name: layerTwoSeries
    Surface3DSeries {
        id: layerTwoSeries
        baseGradient: layerTwoGradient
        HeightMapSurfaceDataProxy {
            heightMapFile: ":/heightmaps/layer_2.png"
        }
        flatShadingEnabled: false
        drawMode: Surface3DSeries.DrawSurface
        visible: true // bind to checkbox state
    }
}
