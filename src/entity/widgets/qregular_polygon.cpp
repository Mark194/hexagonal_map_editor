#include "qregular_polygon.hpp"


#include <cmath>
#include <stdexcept>


#include <QBrush>
#include <QFont>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>


void QRegularPolygon::setCoord(const QString & coord)
{
    m_coord = coord;
}

QString QRegularPolygon::coord() const
{
    return m_coord;
}

QRegularPolygon::QRegularPolygon(double sides,
                                 double radius,
                                 QPointF center,
                                 double angle,
                                 QGraphicsItem *  parent)
    : QGraphicsPolygonItem( parent )
{
    if ( sides < 3 )

        throw std::logic_error( "A regular polygon at least has 3 sides." );


    m_sides  = sides;

    m_radius = radius;

    m_angle  = angle;

    m_center = center;


    setFlags( QGraphicsItem::ItemIsSelectable );

    draw();
}

void QRegularPolygon::addText(QString text)
{
    QGraphicsSimpleTextItem * item = new QGraphicsSimpleTextItem( text, this );

    auto font = item->font();

    font.setPointSize( 4 );

    item->setFont( font );

    auto rect = item->boundingRect();

    rect.moveCenter( boundingRect().center() );

    QPointF pos = rect.topLeft();

    pos.setY( pos.y() - m_radius / 2 - 4 );

    item->setPos( pos );
}

void QRegularPolygon::addImage(QString source)
{
    if ( source.isEmpty() ) return;

    QPixmap pixmap( source );

    if ( pixmap.isNull() ) return;

    QGraphicsSvgItem * item = new QGraphicsSvgItem( source, this );

    auto rect = item->boundingRect();

    rect.moveCenter( boundingRect().center() );

    item->setPos( rect.topLeft() );
}

void QRegularPolygon::addColor(QString color)
{
    QColor shapeColor( color );


    if ( not shapeColor.isValid() ) return;


    setBrush( QBrush( shapeColor, Qt::SolidPattern ) );
}

void QRegularPolygon::draw()
{
    QVector<QPointF> points;

    double angle {0};

    double x, y;

    for ( int i = 0; i < m_sides; i++ )
    {
        angle = m_angle + ( 2 * M_PI * i / m_sides );

        x = m_center.x() + ( m_radius * cos(angle) );

        y = m_center.y() + ( m_radius * sin(angle) );

        points.append( { x, y } );
    }

    setPolygon( { points } );
}
