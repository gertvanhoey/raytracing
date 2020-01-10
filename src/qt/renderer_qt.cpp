#include "renderer_qt.h"
#include "world.h"
#include <QThread>
#include <fstream>

RayTracer::RayTracer(QObject* parent) :
    QObject(parent),
    m_size(0, 0),
    m_maxNumRaysPerPixel(1000),
    m_world(World::randomSceneHierarchy()),
    m_camera(nullptr),
    m_image(QSize(0, 0), QImage::Format_RGB888),
    m_numRaysPerPixel(0)
{
}

QSize RayTracer::size() const
{
    return m_size;
}

void RayTracer::setSize(QSize size)
{
    if (m_size != size) {
        m_size = size;
        createCamera();
        emit sizeChanged();
    }
}

int RayTracer::maxNumRaysPerPixel() const
{
    return m_maxNumRaysPerPixel;
}

void RayTracer::setMaxNumRaysPerPixel(int maxNumRaysPerPixel)
{
    if (m_maxNumRaysPerPixel != maxNumRaysPerPixel) {
        m_maxNumRaysPerPixel = maxNumRaysPerPixel;
        emit maxNumRaysPerPixelChanged();
    }
}

QImage RayTracer::image() const
{
    return m_image;
}

int RayTracer::numRaysPerPixel() const
{
    return m_numRaysPerPixel;
}

void RayTracer::start()
{
    auto worker = new RayTracerWorker(m_world.get(), m_camera.get(), m_size, m_maxNumRaysPerPixel);
    auto thread = new QThread;
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &RayTracerWorker::process);
    connect(worker, &RayTracerWorker::imageAvailable, this, &RayTracer::onImageAvailable);
    connect(worker, &RayTracerWorker::finished, thread, &QThread::quit);
    connect(worker, &RayTracerWorker::finished, worker, &RayTracerWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}

void RayTracer::stop()
{

}

void RayTracer::onImageAvailable(QImage image, int numRaysPerPixel)
{
    m_image = std::move(image);
    m_numRaysPerPixel = numRaysPerPixel;
    emit imageChanged();
    emit numRaysPerPixelChanged();
}

void RayTracer::createCamera()
{
    const Vec3 lookFrom(12.0, 2.0, 4.0);
    const Vec3 lookAt(0.0, 0.0, 0.0);
    const double distanceToFocus = (lookFrom - lookAt).length();
    const double aperture = 0.0;
    m_camera = std::make_unique<Camera>(lookFrom, lookAt, Vec3(0.0, 1.0, 0.0), 30.0,
                                        double(m_size.width()) / double(m_size.height()),
                                        aperture, distanceToFocus);
}

RayTracerWorker::RayTracerWorker(Object* world, Camera* camera, QSize size, int maxNumRaysPerPixel) :
    m_world(world),
    m_camera(camera),
    m_size(size),
    m_numRaysPerPixel(0),
    m_maxNumRaysPerPixel(maxNumRaysPerPixel),
    m_renderer(size.width(), size.height())
{
}

void RayTracerWorker::process()
{
    const size_t w = m_size.width();
    const size_t h = m_size.height();
    if (w * h > 0) {
        while (m_numRaysPerPixel < m_maxNumRaysPerPixel) {
            auto pixels = m_renderer.renderIncremental(*m_world, *m_camera, 1);
            std::vector<unsigned char> imageData(w * h * 4, 255u);
            for (size_t row = 0; row < h; row++) {
                for (size_t col = 0; col < w; col++) {
                    const auto R = pixels(col, row).r();
                    const auto G = pixels(col, row).g();
                    const auto B = pixels(col, row).b();
                    const auto r = (unsigned char)(255.99 * sqrt(pixels(col, row).r()));
                    const auto g = (unsigned char)(255.99 * sqrt(pixels(col, row).g()));
                    const auto b = (unsigned char)(255.99 * sqrt(pixels(col, row).b()));
                    imageData[4 * w * row + 4 * col + 0] = b;
                    imageData[4 * w * row + 4 * col + 1] = g;
                    imageData[4 * w * row + 4 * col + 2] = r;
                }
            }
            QImage image(const_cast<const uchar *>(imageData.data()), int(w), int(h), QImage::Format_RGB32);
            image.bits();
            m_numRaysPerPixel++;
            Q_EMIT imageAvailable(image, m_numRaysPerPixel);
        }
    }
    Q_EMIT finished();
}

void RayTracerWorker::save_to_ppm(const std::string &filename, const Array2D<Vec3> &pixels, int width, int height)
{
    std::ofstream output;
    output.open(filename);
    output << "P3\n" << width << " " << height << "\n255\n";
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            const Vec3 pixel = pixels(i, j);
            Vec3 encodedPixel(sqrt(pixel[0]), sqrt(pixel[1]), sqrt(pixel[2]));
            Vec3 scaledPixel(255.99 * encodedPixel.r(), 255.99 * encodedPixel.g(), 255.99 * encodedPixel.b());

            output << int(scaledPixel.r()) << " " << int(scaledPixel.g()) << " " << int(scaledPixel.b()) << "\n";
        }
    }
    output.close();
}

