#include "regulatory.hpp"
#include "qdebug.h"


#include <cmath>


#include <QApplication>


#include <entity/controls/mover.hpp>
#include <entity/controls/zoomer.hpp>

#include <parser/map_parser.hpp>


Regulatory::Regulatory()
{
    m_hexGrid = new HexGrid( { 0.0, 0.0, 500.0, 500.0 } );


    Zoomer * zoomer = new Zoomer( m_hexGrid );

    zoomer->setModifiers( Qt::NoModifier );

    m_objects.append( zoomer );


    Mover * mover = new Mover( m_hexGrid );

    m_objects.append( mover );
}

void Regulatory::run()
{
    auto polygons = create( 47, 16 );

    createCoords( polygons, 32 );

    m_hexGrid->show();


    try
    {
        MapParser parser;

        auto mapStruct = parser.load( qApp->applicationDirPath() + "/map.json" );

        loadStyles( polygons, mapStruct, {} );
    }
    catch ( std::logic_error & err )
    {
        qApp->exit( -1 );
    }


}

QList<QRegularPolygon *> Regulatory::create(int rows, int columns)
{
    double radius = 50;

    int ri = int( radius / 2 * sqrt( 3 ) );

    int sides = 6;


    int apothem = int( ri * cos( M_PI / sides ) );

    int side = int( 2 * apothem * tan( M_PI / sides ) );


    int initX = 50;

    int initY = 50;

    double angle = M_PI / 2;


    QList<QRegularPolygon *> polygons;

    for ( int x = initX; x < (initX + rows); x++ )
    {
        double timesX  = x - initX;

        double centerX = x + ( 2 * apothem - 1 ) * timesX;

        for ( int y = initY; y < (initY + columns); y++ )
        {
            double timesY  = y - initY;

            double centerY = y + (( 2 * ri ) + side ) * timesY;

            QPointF centerOne( centerX, centerY );

            QPointF centerTwo( centerX + apothem, centerY + ri + side / 2 );


            auto h1 = new QRegularPolygon( sides, ri, centerOne, angle );

            auto h2 = new QRegularPolygon( sides, ri, centerTwo, angle );

            polygons.append( { h1, h2 } );


            m_hexGrid->scene()->addItem( h1 );

            m_hexGrid->scene()->addItem( h2 );
        }
    }

    return polygons;
}

const char * COORD_FMT = "%1,%2";

void Regulatory::createCoords(QList<QRegularPolygon *> & polygons, int columns)
{
    int row = 0, count = 0;

    for ( auto & polygon : polygons )
    {
        auto coord = QString( COORD_FMT ).arg( row ).arg( count );

        polygon->addText( coord );

        polygon->setCoord( coord );

        count++;

        if ( count >= columns )
        {
            row++;

            count = 0;
        }
    }
}

void Regulatory::loadStyles(QList<QRegularPolygon *> & polygons, MapDict & config, StylesDict styles)
{

}
