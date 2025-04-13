#include "async_map_worker.hpp"


#include <QSize>
#include <QtConcurrent>


#include <services/hex_map_manager.hpp>

#include <entity/adapter/gui_state_provider.hpp>


AsyncMapWorker::AsyncMapWorker(EditorWindow * window, QObject * parent)
    : QObject( parent ),
      m_watcher( new HexGridWatcher( this ) ),
      m_editor( window )
{
    connect( m_watcher, &HexGridWatcher::finished,
             this,      &AsyncMapWorker::handleGenerationFinished );
}

AsyncMapWorker::~AsyncMapWorker()
{
    cancelGeneration();
}

void AsyncMapWorker::startGeneration(const QSize & mapSize)
{
    if ( m_isRunning ) cancelGeneration();


    if ( mapSize.isEmpty() )
    {
        emit generationCanceled();
        return;
    }

    m_isRunning = true;
    emit generationStarted();

    auto future = QtConcurrent::run( &HexMapManager::generateCells, mapSize);

    m_watcher->setFuture(future);
}

void AsyncMapWorker::cancelGeneration()
{
    if ( not m_isRunning ) return;

    m_watcher->cancel();

    m_isRunning = false;

    emit generationCanceled();
}

void AsyncMapWorker::handleGenerationFinished()
{
    m_isRunning = false;

    if ( m_watcher->isCanceled() )
    {
        emit generationCanceled();
        return;
    }

    try
    {
        auto cells = m_watcher->result();

        GuiStateProvider::clearCells( m_editor );

        GuiStateProvider::loadCells( m_editor, cells );

        emit generationFinished();
    }
    catch (...)
    {
        emit generationCanceled();
    }
}
