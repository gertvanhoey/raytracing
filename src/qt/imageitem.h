#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "raytracing_qt_export.h"
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>

class RAYTRACING_QT_EXPORT ImageItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    ImageItem(QQuickItem* parent = nullptr);
    QImage image() const;
    Q_INVOKABLE void setImage(const QImage& image);
    void paint(QPainter* painter) override;

signals:
    void imageChanged();

private:
    QImage m_image;
};

#endif // IMAGEITEM_H
