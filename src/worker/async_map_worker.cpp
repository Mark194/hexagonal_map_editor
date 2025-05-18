#include "async_map_worker.hpp"


#include <QtConcurrent>


#include "../services/hex_map_manager.hpp"

#include "../entity/adapter/gui_state_provider.hpp"


AsyncMapWorker::AsyncMapWorker(EditorWindow * window, QObject * parent)
    : QObject( parent ),
      m_syncWatcher( new SyncWatcher( this ) ),
      m_cellWatcher( new HexGridWatcher( this ) ),
      m_coordsWatcher( new CoordWatcher( this ) ),
      m_editor( window )
{
    m_synchronizer.setCancelOnWait( false );

    connect( m_cellWatcher, &HexGridWatcher::finished,
             this,          &AsyncMapWorker::handleCellsFinished );

    connect( m_coordsWatcher, &CoordWatcher::finished,
             this,            &AsyncMapWorker::handleCoordsFinished );

    connect(m_syncWatcher, &SyncWatcher::finished,
            this,          &AsyncMapWorker::handleSyncFinished );
}

AsyncMapWorker::~AsyncMapWorker()
{
    cancelGeneration();

    delete m_cellWatcher;
    delete m_coordsWatcher;
    delete m_syncWatcher;
}

static void synchronizeWrapper(QFutureSynchronizer<void> * sync)
{
    sync->waitForFinished();
}

void AsyncMapWorker::startGeneration(const QSize & mapSize, const bool isRotate)
{
    if ( m_isRunning.exchange( true ) ) cancelGeneration();


    if ( mapSize.isEmpty() )
    {
        emit generationCanceled();
        return;
    }

    m_isRunning = true;

    emit generationStarted();

    auto cellFuture = QtConcurrent::run(
        &HexMapManager::generateCells,
        mapSize,
        isRotate
    );

    auto coordFuture = QtConcurrent::run(
        &HexMapManager::generateCoord,
        mapSize
    );

    m_synchronizer.addFuture( cellFuture );

    m_synchronizer.addFuture( coordFuture );


    m_cellWatcher->setFuture( cellFuture );

    m_coordsWatcher->setFuture( coordFuture );

    auto syncFuture = QtConcurrent::run( synchronizeWrapper, &m_synchronizer );

    m_syncWatcher->setFuture( syncFuture );
}

void AsyncMapWorker::cancelGeneration()
{
    if ( not m_isRunning ) return;

    m_cellWatcher->cancel();

    m_isRunning = false;

    emit generationCanceled();
}

void AsyncMapWorker::handleCellsFinished()
{
    if ( m_cellWatcher->isCanceled() ) return;

    m_generatedCells = m_cellWatcher->result();
}

void AsyncMapWorker::handleCoordsFinished()
{

    if ( m_coordsWatcher->isCanceled() ) return;

    m_generatedCoords = m_coordsWatcher->result();
}

void AsyncMapWorker::handleSyncFinished()
{
    if ( not m_isRunning ) return;

    if ( isAllFuturesFinished() )
        combineResults();
    else
        emit generationCanceled();

    cleanup();
}

void AsyncMapWorker::combineResults()
{
    if (m_generatedCells.size() != m_generatedCoords.size())
    {
        emit generationCanceled();
        return;
    }


    GuiStateProvider::loadCoords( m_generatedCells, m_generatedCoords );

    GuiStateProvider::clearCells( m_editor );

    GuiStateProvider::loadCells(m_editor, m_generatedCells);

    emit generationFinished();
}

void AsyncMapWorker::cleanup()
{
    m_generatedCells.clear();

    m_generatedCoords.clear();

    m_synchronizer.clearFutures();
}

bool AsyncMapWorker::isAllFuturesFinished() const {
    bool isAllFinished = true;

    for ( const auto& future : m_synchronizer.futures() )

        isAllFinished &= future.isFinished();

    return isAllFinished;
}
