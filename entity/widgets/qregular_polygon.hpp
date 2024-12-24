#pragma once


#include <QGraphicsPolygonItem>


class QRegularPolygon : public QGraphicsPolygonItem
{
    double  m_sides;

    double  m_radius;

    double  m_angle;

    QPointF m_center;

public:
    QRegularPolygon(double sides,
                    double radius,
                    QPointF center,
                    double angle  = 0.0,
                    QGraphicsItem * parent = nullptr );

    void addText( QString text );

    void addImage( QString source );

private:

    void draw();

};
