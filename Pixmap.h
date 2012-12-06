#ifndef PIXMAP_H
#define PIXMAP_H

#include <QGraphicsPixmapItem>

class Pixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(QTransform transform READ transform WRITE setTransform)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    Pixmap(const QPixmap &pix)
        : QObject(), QGraphicsPixmapItem(pix)
    {
        setCacheMode(DeviceCoordinateCache);
    }
};

#endif // PIXMAP_H
