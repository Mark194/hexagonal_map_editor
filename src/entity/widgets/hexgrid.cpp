#include "hexgrid.hpp"

HexGrid::HexGrid(const QRectF & rect, QWidget * parent)
    : QGraphicsView( parent )
{
    setScene( new QGraphicsScene() );

    setSceneRect( rect );


    setRenderHint( QPainter::Antialiasing );

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}
