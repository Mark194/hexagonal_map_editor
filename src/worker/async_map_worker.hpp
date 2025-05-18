#pragma once


#include <QObject>
#include <QFutureWatcher>
#include <QFutureSynchronizer>


#include "../static/types.hpp"


using HexGridWatcher = QFutureWatcher<HexGridCells>;

using CoordWatcher   = QFutureWatcher<QStringList>;

using SyncWatcher    = QFutureWatcher<void>;

class EditorWindow;


class AsyncMapWorker : public QObject
{
    Q_OBJECT

    QFutureSynchronizer<void> m_synchronizer;

    SyncWatcher     * m_syncWatcher{};

    HexGridWatcher  * m_cellWatcher{};

    CoordWatcher    * m_coordsWatcher{};

    EditorWindow    * m_editor;

    HexGridCells      m_generatedCells{};

    QStringList       m_generatedCoords;

    std::atomic_bool  m_isRunning{false};

public:

    explicit AsyncMapWorker(EditorWindow * window, QObject * parent = nullptr);

    ~AsyncMapWorker() override;


    void startGeneration(const QSize & mapSize, bool isRotate);

    void cancelGeneration();

Q_SIGNALS:

    void generationStarted();

    void generationFinished();

    void generationCanceled();


private slots:

    void handleCellsFinished();

    void handleCoordsFinished();

    void handleSyncFinished();

private:

    void combineResults();

    void cleanup();

    bool isAllFuturesFinished() const;
};

