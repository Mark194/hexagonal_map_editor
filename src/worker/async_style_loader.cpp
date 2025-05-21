#include "async_style_loader.hpp"


#include <QtConcurrent>


#include "../entity/adapter/gui_state_provider.hpp"
#include "../parser/map_parser.hpp"


AsyncStyleLoader::AsyncStyleLoader()
{
    connect( &m_parseWatcher, &MapDictWatcher::finished, this, &AsyncStyleLoader::loadStyles );
}

AsyncStyleLoader::~AsyncStyleLoader() = default;

void AsyncStyleLoader::setStyles(const StylesDict & styles)
{
    m_stylesDict = styles;
}

void AsyncStyleLoader::setCells(const HexGridCells & cells)
{
    m_gridCells = cells;
}

void AsyncStyleLoader::start(const QString & fileName)
{
    Q_ASSERT_X( m_stylesDict.isEmpty(), "AsyncStyleLoader::start()", "Styles dictionary is empty!" );


    m_parseFuture = QtConcurrent::run( &MapParser::load, fileName );

    m_parseWatcher.setFuture( m_parseFuture );
}

void AsyncStyleLoader::loadStyles() const
{
    while ( m_gridCells.isEmpty() )
        qApp->processEvents();

    auto mapDict = m_parseFuture.result();

    GuiStateProvider::loadStyles( m_gridCells, mapDict, m_stylesDict );
}
