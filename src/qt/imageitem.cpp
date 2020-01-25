#include "imageitem.h"

ImageItem::ImageItem(QQuickItem* parent) : QQuickPaintedItem(parent) {}

QImage ImageItem::image() const
{
    return m_image;
}

void ImageItem::setImage(const QImage& image)
{
    m_image = image;

    update();
}

void ImageItem::paint(QPainter* painter)
{
    if (!m_image.isNull()) {
        QRectF rect = boundingRect();
        QImage scaledImage = m_image.scaledToHeight(int(rect.height()));
        QPointF center = rect.center() - scaledImage.rect().center();

        if (center.x() < 0.0) {
            center.setX(0.0);
        }
        if (center.y() < 0.0) {
            center.setY(0.0);
        }
        painter->drawImage(center, scaledImage);
    }
}
