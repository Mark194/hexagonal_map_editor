#include "regulatory.hpp"


#include <cmath>


#include <QApplication>
#include <QSvgGenerator>
#include <QtConcurrent>


#include <entity/adapter/gui_state_provider.hpp>
#include <entity/controls/mover.hpp>
#include <entity/controls/zoomer.hpp>

#include <parser/map_parser.hpp>
#include <parser/map_styles_parser.hpp>

#include <form/map_size_editor.hpp>


#include <services/hex_map_manager.hpp>


Regulatory::Regulatory()
    : m_editor( new EditorWindow( this ) ),
      m_worker( new AsyncMapWorker( m_editor, this ) )
{

}

Regulatory::~Regulatory()
{
    delete m_editor;

    delete m_worker;
}

void Regulatory::run()
{

    m_editor->showMaximized();


    GuiStateProvider::createRelations( m_editor );

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

void Regulatory::notifyCreateMap()
{
    auto mapSizeEditor = new MapSizeEditor;

    mapSizeEditor->setWindowTitle( "Окно создания карты" );


    if ( mapSizeEditor->exec() != QDialog::Accepted ) return;


    auto mapSize      = mapSizeEditor->mapSize();

    auto isRotateCell = mapSizeEditor->isRotate();

    m_worker->startGeneration( mapSize, isRotateCell );
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
    // auto scene = m_hexGrid->scene();

    // scene->clearSelection();

    // scene->setSceneRect( scene->itemsBoundingRect() );

    // QImage img( scene->sceneRect().size().toSize(), QImage::Format_ARGB32 );

    // img.fill( Qt::black );

    // QPainter painter( &img );

    // scene->render( &painter );

    // img.save( "./map.png" );
}

void Regulatory::saveToSvg()
{
    // auto scene = m_hexGrid->scene();

    // QSvgGenerator generator;        // Create a file generator object
    // generator.setFileName( qApp->applicationDirPath() + "/map.svg" );    // We set the path to the file where to save vector graphics
    // generator.setSize(QSize(scene->width(), scene->height()));  // Set the dimensions of the working area of the document in millimeters
    // generator.setViewBox(QRect(0, 0, scene->width(), scene->height())); // Set the work area in the coordinates
    // generator.setTitle( "SVG Example" );                          // The title document
    // generator.setDescription( "File created by SVG Example" );

    // QPainter painter;
    // painter.begin(&generator);
    // scene->render(&painter);
    // painter.end();
}
