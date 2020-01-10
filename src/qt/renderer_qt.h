#ifndef RENDERER_QT_H
#define RENDERER_QT_H

#include "raytracing_qt_export.h"
#include <QObject>
#include <QSize>
#include <QImage>
#include "renderer.h"
#include "object.h"
#include "camera.h"
#include <memory>
#include <string>

class QThread;

class RAYTRACING_QT_EXPORT RayTracer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int maxNumRaysPerPixel READ maxNumRaysPerPixel WRITE setMaxNumRaysPerPixel NOTIFY maxNumRaysPerPixelChanged)
    Q_PROPERTY(QImage image READ image NOTIFY imageChanged)
    Q_PROPERTY(int numRaysPerPixel READ numRaysPerPixel NOTIFY numRaysPerPixelChanged)

public:
    explicit RayTracer(QObject* parent = nullptr);

    QSize size() const;
    void setSize(QSize size);

    int maxNumRaysPerPixel() const;
    void setMaxNumRaysPerPixel(int num);

    QImage image() const;

    int numRaysPerPixel() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void sizeChanged();
    void maxNumRaysPerPixelChanged();
    void imageChanged();
    void numRaysPerPixelChanged();

private slots:
    void onImageAvailable(QImage image, int numRaysPerPixel);

private:
    void createCamera();

private:
    QSize m_size;
    int m_maxNumRaysPerPixel;
    std::unique_ptr<Object> m_world;
    std::unique_ptr<Camera> m_camera;
    QImage m_image;
    int m_numRaysPerPixel;
};

// https://wiki.qt.io/QThreads_general_usage

class RAYTRACING_QT_EXPORT RayTracerWorker : public QObject
{
    Q_OBJECT
public:
    RayTracerWorker(Object* world, Camera* camera, QSize size, int maxNumRaysPerPixel);

public slots:
    void process();

signals:
    void imageAvailable(QImage image, int numRaysPerPixel);
    void finished();

private:
    static void save_to_ppm(const std::string& filename, const Array2D<Vec3>& pixels, int width, int height);

private:
    Object* m_world;
    Camera* m_camera;
    QSize m_size;
    int m_numRaysPerPixel;
    int m_maxNumRaysPerPixel;
    Renderer m_renderer;
};

#endif // RENDERER_QT_H
