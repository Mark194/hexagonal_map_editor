#pragma once


#include <QGraphicsSvgItem>


class QRegularPolygon : public QGraphicsPolygonItem
{
    double m_sides;

    double m_radius;

    double m_angle;

    QPointF m_center;

    QString m_coord;

    QString m_image;

    QGraphicsSvgItem * m_imageItem;

public:
    QRegularPolygon
    (double sides, double radius, const QPointF & center, double angle = 0.0, QGraphicsItem * parent = nullptr);

    void addText(const QString & text);

    void addImage(const QString & source);

    QString image() const;

    void clearImage();

    void setColor(const QString & color);

    void setColor(const QColor & color);


    void setCoord(const QString & coord);

    [[nodiscard]] QString coord() const;

private:
    void draw();
};
