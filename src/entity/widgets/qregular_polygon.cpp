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

QRegularPolygon::QRegularPolygon
(const double sides, const double radius, const QPointF & center, const double angle, QGraphicsItem * parent)
    : QGraphicsPolygonItem( parent )
  , m_imageItem( new QGraphicsSvgItem( this ) )
{
    if ( sides < 3 )

        throw std::logic_error( "A regular polygon at least has 3 sides." );


    m_sides = sides;

    m_radius = radius;

    m_angle = angle;

    m_center = center;


    setFlags( ItemIsSelectable );

    draw();
}

void QRegularPolygon::addText(const QString & text)
{
    const auto item = new QGraphicsSimpleTextItem( text, this );

    auto font = item->font();

    font.setPointSize( 4 );

    item->setFont( font );

    auto rect = item->boundingRect();

    rect.moveCenter( boundingRect().center() );

    QPointF pos = rect.topLeft();

    pos.setY( pos.y() - m_radius / 2 - 4 );

    item->setPos( pos );
}

void QRegularPolygon::addImage(const QString & source)
{
    if ( source.isEmpty() )
        return;

    QPixmap pixmap( source );
    if ( pixmap.isNull() )
        return;

    m_image = source;

    const auto render = new QSvgRenderer( source );

    m_imageItem->setSharedRenderer( render );

    QRectF itemRect = m_imageItem->boundingRect();
    const QRectF polygonRect = boundingRect();

    constexpr qreal scale = 0.25;
    m_imageItem->setScale( scale );
    itemRect = QRectF( 0, 0, itemRect.width() * scale, itemRect.height() * scale );


    const QPointF centerOffset = polygonRect.center() - itemRect.center();

    m_imageItem->setPos( centerOffset );
}

QString QRegularPolygon::image() const
{
    return m_image;
}

void QRegularPolygon::clearImage()
{
    QByteArray emptySvg = "<svg xmlns='http://www.w3.org/2000/svg'/>";
    auto emptyRenderer = new QSvgRenderer( emptySvg );

    m_imageItem->setSharedRenderer( emptyRenderer );
}

void QRegularPolygon::setColor(const QString & color)
{
    const QColor shapeColor( color );

    setColor( shapeColor );
}

void QRegularPolygon::setColor(const QColor & color)
{
    if ( not color.isValid() )
        return;

    setBrush( QBrush( color, Qt::SolidPattern ) );
}

void QRegularPolygon::draw()
{
    QVector<QPointF> points;

    double angle{ 0 };

    for ( int i = 0; i < m_sides; ++i )
    {
        angle = m_angle + ( 2 * M_PI * i / m_sides );

        double x = m_center.x() + ( m_radius * cos( angle ) );

        double y = m_center.y() + ( m_radius * sin( angle ) );

        points.append( { x, y } );
    }

    setPolygon( { points } );
}
