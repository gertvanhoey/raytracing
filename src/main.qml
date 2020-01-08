import QtQuick 2.6
import QtQuick.Controls 2.0
import raytracer 1.0

ApplicationWindow {
    id: root
    width: 1920
    height: 1080
    visible: true

    RayTracer {
        id: raytracer
        size.width: root.width
        size.height: root.height
        maxNumRaysPerPixel: 100
        Component.onCompleted: raytracer.start()
    }

    ImageItem {
        id: image
        width: parent.width
        height: parent.height
        image: raytracer.image
    }

    Text {
        id: counter
        text: raytracer.numRaysPerPixel
        font.pixelSize: 24
        anchors.top: image.top
    }
}
