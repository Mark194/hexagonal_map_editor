//
// Created by Женя on 21.06.2025.
//

#include "fill_color_command.hpp"

#include <QBrush>
#include <qset.h>


FillColorCommand::FillColorCommand(QRegularPolygon * shape, const QColor & color, const HexGridCells & polygons)
    : ChangeColorCommand( shape, color )
  , m_adjacentPolygons( findMatchingPolygons( shape, polygons ) ) {}

void FillColorCommand::undo()
{
    for ( auto polygon : m_adjacentPolygons )
        polygon->setColor( m_oldColor );
}

void FillColorCommand::redo()
{
    for ( auto polygon : m_adjacentPolygons )
        polygon->setColor( m_color );
}

bool polygonsTouch(const QRegularPolygon * a, const QRegularPolygon * b)
{
    return a->boundingRect().intersects( b->boundingRect() );
}

HexGridCells FillColorCommand::findMatchingPolygons(QRegularPolygon * current, const HexGridCells & polygons)
{
    HexGridCells result;
    if ( !current || polygons.isEmpty() )
        return result;

    QSet<int> processedIndices;

    HexGridCells queue;


    const QColor targetColor = current->brush().color();

    int startIndex = -1;
    for ( int i = 0; i < polygons.size(); ++i )
    {
        if ( polygons[ i ] == current )
        {
            startIndex = i;
            break;
        }
    }
    if ( startIndex == -1 )
        return result;

    queue.append( current );
    processedIndices.insert( startIndex );

    while ( !queue.isEmpty() )
    {
        QRegularPolygon * currentPoly = queue.takeFirst();
        result.append( currentPoly );

        for ( int i = 0; i < polygons.size(); ++i )
        {
            if ( processedIndices.contains( i ) )
                continue;

            QRegularPolygon * neighbor = polygons[ i ];
            if ( neighbor->brush().color() != targetColor )
                continue;

            if ( polygonsTouch( currentPoly, neighbor ) )
            {
                queue.append( neighbor );
                processedIndices.insert( i );
            }
        }
    }

    return result;
}
