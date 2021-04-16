import QtQuick 2.0
import QtDataVisualization 1.2

Item {
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
}
