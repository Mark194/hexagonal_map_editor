#include "regulatory.hpp"
#include "qdebug.h"


#include <cmath>


#include <QApplication>
#include <QSvgGenerator>


#include <entity/controls/mover.hpp>
#include <entity/controls/zoomer.hpp>

#include <parser/map_parser.hpp>
#include <parser/map_styles_parser.hpp>


Regulatory::Regulatory()
{
    m_hexGrid = new HexGrid( { 0.0, 0.0, 500.0, 500.0 } );


    Zoomer * zoomer = new Zoomer( m_hexGrid );

    zoomer->setModifiers( Qt::NoModifier );

    m_objects.append( zoomer );


    Mover * mover = new Mover( m_hexGrid );

    m_objects.append( mover );
}

Regulatory::~Regulatory()
{
    qDeleteAll( m_objects );

    m_objects.clear();


    delete m_editor;
}

void Regulatory::run()
{

    m_editor = new EditorWindow;

    m_editor->show();


    // m_hexGrid->setUpdatesEnabled( false );


    // auto polygons = create( 100, 50 );

    // createCoords( polygons, 100 );



    // try
    // {
    //     MapParser parserMapStruct;

    //     auto mapStruct = parserMapStruct.load( qApp->applicationDirPath() + "/map.json" );


    //     MapStylesParser parserStyles;

    //     auto styles = parserStyles.load( qApp->applicationDirPath() + "/styles.json" );

    //     loadStyles( polygons, mapStruct, styles );
    // }
    // catch ( std::logic_error & err )
    // {
    //     qApp->exit( -1 );
    // }


    // qApp->sync();

    // saveToFile();

    // saveToSvg();

    // m_hexGrid->setUpdatesEnabled( true );

    // m_hexGrid->show();
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


const char * COORD_FMT = "%1, %2";


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
    for ( auto polygon : polygons )
    {
        QString polygonCoord = polygon->coord();

        auto styleCoord = config[polygonCoord];

        if ( styleCoord.style == "default" )

            continue;

        auto styleMap = styles.value( styleCoord.style );

        if ( styleCoord.customColor.isEmpty() )

            polygon->addColor( styleMap.color );

        else

            polygon->addColor( styleCoord.customColor );

        polygon->addImage( styleMap.image );
    }
}

void Regulatory::saveToFile()
{
    auto scene = m_hexGrid->scene();

    scene->clearSelection();

    scene->setSceneRect( scene->itemsBoundingRect() );

    QImage img( scene->sceneRect().size().toSize(), QImage::Format_ARGB32 );

    img.fill( Qt::black );

    QPainter painter( &img );

    scene->render( &painter );

    img.save( "./map.png" );
}

void Regulatory::saveToSvg()
{
    auto scene = m_hexGrid->scene();

    QSvgGenerator generator;        // Create a file generator object
    generator.setFileName( qApp->applicationDirPath() + "/map.svg" );    // We set the path to the file where to save vector graphics
    generator.setSize(QSize(scene->width(), scene->height()));  // Set the dimensions of the working area of the document in millimeters
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height())); // Set the work area in the coordinates
    generator.setTitle( "SVG Example" );                          // The title document
    generator.setDescription( "File created by SVG Example" );

    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();
}
