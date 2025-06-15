#include "regulatory.hpp"


#include <cmath>
#include <iostream>


#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QSvgGenerator>


#include "entity/adapter/gui_state_provider.hpp"
#include "entity/adapter/struct_map_adapter.h"
#include "entity/controls/mover.hpp"
#include "entity/controls/scene_click_handler.hpp"
#include "saver/map_saver.hpp"

#include "parser/map_parser.hpp"

#include "form/map_size_editor.hpp"
#include "parser/map_styles_parser.hpp"
#include "worker/async_style_loader.hpp"


Regulatory::Regulatory()
    : m_editor( new EditorWindow( this ) )
  , m_worker( new AsyncMapWorker( m_editor, this ) )
  , m_commandManager( new CommandManager( GuiStateProvider::hexView( m_editor ) ) ) {}

Regulatory::~Regulatory()
{
    delete m_editor;

    delete m_worker;
}

void Regulatory::run()
{
    m_editor->showMaximized();


    GuiStateProvider::createRelations( m_editor );


    try
    {
        loadStyles( qApp->applicationDirPath() + "/styles.json" );
    }
    catch ( const std::logic_error & error )
    {
        QString errorMessage = "Ошибка загрузки стилей:\n";

        QMessageBox::critical( m_editor, "Ошибка", errorMessage + error.what() );
    }
}

void Regulatory::notifyCreateMap()
{
    const auto mapSizeEditor = new MapSizeEditor;

    mapSizeEditor->setWindowTitle( "Окно создания карты" );


    if ( mapSizeEditor->exec() != QDialog::Accepted )
        return;


    const auto mapSize = mapSizeEditor->mapSize();

    const auto isRotateCell = mapSizeEditor->isRotate();

    m_worker->startGeneration( mapSize, isRotateCell );
}

void Regulatory::notifyOpenMap()
{
    const QString fileName = QFileDialog::getOpenFileName( m_editor,
                                                           "Окно выбора карты",
                                                           qApp->applicationDirPath(),
                                                           "Файл карты (*.json)" );

    if ( fileName.isEmpty() )
        return;

    const auto mapDict = MapParser::load( fileName );

    const auto maxElement = StructMapAdapter::findMaxElement( mapDict.keys() );

    const auto maxSize = StructMapAdapter::maxSize( maxElement );


    auto styleLoader = new AsyncStyleLoader;

    styleLoader->setStyles( m_styles );

    connect( m_worker, &AsyncMapWorker::cellChanged, styleLoader, &AsyncStyleLoader::setCells );
    m_worker->startGeneration( maxSize, true );

    styleLoader->start( fileName );
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

    if ( fileName.isEmpty() )
        return;

    try
    {
        auto saver = MapSaver::saver( selectedFilter );

        auto scene = GuiStateProvider::scene( m_editor );

        saver->save( fileName, scene );

        QMessageBox::information( m_editor, "Окно сообщения", "Успешно сохранено!" );
    }
    catch ( const std::logic_error & err )
    {
        QMessageBox::critical( m_editor, "Окно ошибки", err.what() );
    }
}

void Regulatory::notifyQuit()
{
    qApp->exit();
}

void Regulatory::notifyLoadStyles()
{
    const QString fileName = QFileDialog::getOpenFileName( m_editor,
                                                           "Окно выбора файла стилей",
                                                           qApp->applicationDirPath(),
                                                           "Файл стилей (*.json)" );

    if ( fileName.isEmpty() )
        return;

    loadStyles( fileName );
}

void Regulatory::notifyHandleClick()
{
    const auto handler = dynamic_cast<SceneClickHandler *>(sender());

    if ( not handler )
        return;

    const auto shape = handler->currentItem();

    if ( not shape )
        return;

    QUndoCommand * cmd = nullptr;

    switch ( GuiStateProvider::actionType( m_editor ) )
    {
        case ActionType::NoAction:
            return;

        case ActionType::ChangeColor:
        {
            const auto primaryColor = GuiStateProvider::primaryColor( m_editor );

            cmd = CommandManager::create( ActionType::ChangeColor, shape, primaryColor );

            break;
        }
        case ActionType::ChangeStyle:
        {
            try
            {
                const auto selectedStyleName = GuiStateProvider::selectedStyle( m_editor );

                const auto selectedStyle = m_styles.value( selectedStyleName );

                if ( not selectedStyle.isValid() )
                    throw std::logic_error( "unknown style" );

                const auto style = QVariant::fromValue( selectedStyle );

                cmd = CommandManager::create( ActionType::ChangeStyle, shape, style );
            }
            catch ( const std::logic_error & err )
            {
                std::cout << err.what();
            }

            break;
        }
    }

    if ( not cmd )
        return;

    m_commandManager->execute( cmd );
}

void Regulatory::loadStyles(const QString & filename)
{
    auto styles = MapStylesParser::load( filename );

    GuiStateProvider::loadStylesMiniatures( m_editor, styles );

    m_styles = styles;
}
