#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "imageitem.h"
#include "renderer_qt.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<RayTracer>("raytracer", 1, 0, "RayTracer");
    qmlRegisterType<ImageItem>("raytracer", 1, 0, "ImageItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
