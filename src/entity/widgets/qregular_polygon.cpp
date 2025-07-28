#include "qregular_polygon.hpp"


#include <cmath>
#include <iostream>
#include <stdexcept>


#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
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

    for ( int i = NORTHEAST; i <= NORTHWEST; ++i )
    {
        m_images << "";
        m_items << nullptr;
    }

    setFlags( ItemIsSelectable );

    draw();
}

void QRegularPolygon::addText(const QString & text)
{
    const auto item = new QGraphicsSimpleTextItem( text,
                                                   this );

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
    itemRect = QRectF( 0,
                       0,
                       itemRect.width() * scale,
                       itemRect.height() * scale );


    const QPointF centerOffset = polygonRect.center() - itemRect.center();

    m_imageItem->setPos( centerOffset );
}

QString QRegularPolygon::image() const
{
    return m_image;
}

QString QRegularPolygon::image(HexCorner corner) const
{
    return m_images.value( corner );
}

void QRegularPolygon::clearImage()
{
    QByteArray emptySvg = "<svg xmlns='http://www.w3.org/2000/svg'/>";
    auto emptyRenderer = new QSvgRenderer( emptySvg );

    m_imageItem->setSharedRenderer( emptyRenderer );
}

void QRegularPolygon::clearImage(const HexCorner corner)
{
    auto item = m_items.value( corner );

    if ( not item )
        return;

    delete item;

    m_items[ corner ] = nullptr;
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

    setBrush( QBrush( color,
                      Qt::SolidPattern ) );
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

void QRegularPolygon::addImage(const QString & source, HexCorner corner)
{
    auto * svgItem = new QGraphicsSvgItem();
    svgItem->setSharedRenderer( new QSvgRenderer( source ) );

    if ( !svgItem->renderer()->isValid() )
    {
        delete svgItem;
        return;
    }

    // Размеры SVG и шестиугольника
    QRectF svgRect = svgItem->boundingRect();
    QRectF hexRect = boundingRect();
    QPointF hexCenter = hexRect.center();

    // Масштаб изображения (25% от исходного размера)
    constexpr qreal imageScale = 0.35;
    qreal scaledWidth = svgRect.width() * imageScale;
    qreal scaledHeight = svgRect.height() * imageScale;

    // Радиус шестиугольника (расстояние от центра до вершины)
    qreal hexRadius = hexRect.width() / 2;

    // Безопасный радиус (уменьшенный, чтобы изображения не касались границ)
    qreal safeRadius = hexRadius * 0.45; // 70% от исходного радиуса

    // Углы для размещения изображений (смещённые на 45°)
    qreal angle = 0.0;
    switch ( corner )
    {
        case NORTHEAST:
            angle = M_PI / 4;
            break; // 45°
        case SOUTHEAST:
            angle = 3 * M_PI / 4;
            break; // 135°
        case SOUTHWEST:
            angle = 5 * M_PI / 4;
            break; // 225°
        case NORTHWEST:
            angle = 7 * M_PI / 4;
            break; // 315°
    }

    // Позиция внутри безопасной зоны
    QPointF imagePos( hexCenter.x() + safeRadius * cos( angle ),
                      hexCenter.y() + safeRadius * sin( angle ) );

    // Корректируем позицию с учётом размера изображения (центрируем)
    QPointF finalPos( imagePos.x() - scaledWidth / 2,
                      imagePos.y() - scaledHeight / 2 );

    svgItem->setScale( imageScale );
    svgItem->setPos( finalPos );

    m_items[ corner ] = svgItem;
    scene()->addItem( svgItem );
}

[[nodiscard]] QRegularPolygon::HexCorner QRegularPolygon::cornerNearestToMouse(const QPointF & point) const
{
    QPointF relPos = point - m_center; // Смещаем точку в систему координат центра

    if ( relPos.x() >= 0 )
    {
        if ( relPos.y() >= 0 )
            return NORTHEAST; // Верхний правый угол (северо-восток)
        else
            return NORTHWEST; // Нижний правый угол (юго-восток)
    }
    else
    {
        if ( relPos.y() >= 0 )
            return SOUTHEAST; // Верхний левый угол (северо-запад)
        else
            return SOUTHWEST; // Нижний левый угол (юго-запад)
    }
}
