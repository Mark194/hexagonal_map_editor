#include "regulatory.hpp"


#include <cmath>


#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QSvgGenerator>


#include "entity/adapter/gui_state_provider.hpp"
#include "entity/adapter/struct_map_adapter.h"
#include "entity/controls/mover.hpp"
#include "saver/map_saver.hpp"

#include "parser/map_parser.hpp"

#include "form/map_size_editor.hpp"


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

void Regulatory::notifyOpenMap()
{
    QString fileName = QFileDialog::getOpenFileName(m_editor, "Окно выбора карты",
        qApp->applicationDirPath(),
        "Файл карты (*.json)");

    if ( fileName.isEmpty() ) return;

    auto mapDict = MapParser::load(fileName);

    auto maxElement = StructMapAdapter::findMaxElement(mapDict.keys());

    auto maxSize = StructMapAdapter::maxSize(maxElement);

    m_worker->startGeneration(maxSize, true);
}

void Regulatory::notifySaveMap()
{
    QString selectedFilter;

    const QString tempFileName = qApp->applicationDirPath() + "/map";

    const QString formats = MapSaver::supportedFormats();

    const auto fileName = QFileDialog::getSaveFileName( m_editor,
                                                  "Сохранить файл как",
                                                  tempFileName,
                                                  formats,
                                                  &selectedFilter );

    if ( fileName.isEmpty() ) return;

    try
    {
        auto saver = MapSaver::saver(selectedFilter);

        auto scene = GuiStateProvider::scene( m_editor );

        saver->save( fileName, scene );

        QMessageBox::information( m_editor,
                                  "Окно сообщения",
                                  "Успешно сохранено!" );
    }
    catch (const std::logic_error & err)
    {
        QMessageBox::critical(m_editor, "Окно ошибки", err.what() );
    }

}

void Regulatory::notifyQuit()
{
    qApp->exit();
}

// void Regulatory::loadStyles(QList<QRegularPolygon *> & polygons, MapDict & config, const StylesDict& styles)
// {
//     for ( auto polygon : polygons )
//     {
//         QString polygonCoord = polygon->coord();
//
//         auto styleCoord = config[polygonCoord];
//
//         if ( styleCoord.style == "default" )
//
//             continue;
//
//         auto styleMap = styles.value( styleCoord.style );
//
//         if ( styleCoord.customColor.isEmpty() )
//
//             polygon->addColor( styleMap.color );
//
//         else
//
//             polygon->addColor( styleCoord.customColor );
//
//         polygon->addImage( styleMap.image );
//     }
// }
