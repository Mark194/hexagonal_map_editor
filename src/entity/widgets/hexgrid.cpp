#include "hexgrid.hpp"

HexGrid::HexGrid(const QRectF & rect, QWidget * parent)
    : QGraphicsView( parent )
{
    m_scene = new QGraphicsScene;

    setSceneRect( rect );

    setScene( m_scene );


    setRenderHint( QPainter::Antialiasing );

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}
