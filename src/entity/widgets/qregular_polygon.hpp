#pragma once


#include <QGraphicsSvgItem>


class QRegularPolygon : public QGraphicsPolygonItem
{
public:
    enum HexCorner
    {
        NORTHEAST, // Верхний правый угол
        SOUTHEAST, // Нижний правый угол
        SOUTHWEST, // Нижний левый угол
        NORTHWEST  // Верхний левый угол
    };

    QRegularPolygon
    (double sides, double radius, const QPointF & center, double angle = 0.0, QGraphicsItem * parent = nullptr);

    void addText(const QString & text);

    void addImage(const QString & source);

    [[nodiscard]] QString image() const;

    [[nodiscard]] QString image(HexCorner corner) const;

    void clearImage();

    void clearImage(HexCorner corner);

    void setColor(const QString & color);

    void setColor(const QColor & color);


    void setCoord(const QString & coord);

    [[nodiscard]] QString coord() const;

    void addImage(const QString & source, HexCorner corner);

    [[nodiscard]] HexCorner cornerNearestToMouse(const QPointF & point) const;

private:
    double m_sides;

    double m_radius;

    double m_angle;

    QPointF m_center;

    QString m_coord;

    QString m_image;

    QGraphicsSvgItem * m_imageItem;

    QStringList m_images;

    QList<QGraphicsSvgItem *> m_items;

    void draw();
};
