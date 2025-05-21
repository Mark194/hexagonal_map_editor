#pragma once


#include <QGraphicsPolygonItem>


class QRegularPolygon : public QGraphicsPolygonItem
{
    double m_sides;

    double m_radius;

    double m_angle;

    QPointF m_center;

    QString m_coord;

public:
    QRegularPolygon
    (double sides, double radius, const QPointF & center, double angle = 0.0, QGraphicsItem * parent = nullptr);

    void addText(const QString & text);

    void addImage(const QString & source);

    void addColor(const QString & color);


    void setCoord(const QString & coord);

    QString coord() const;

private:
    void draw();
};
