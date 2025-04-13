#pragma once


#include <QObject>
#include <QFutureWatcher>


#include "static/types.hpp"


using HexGridWatcher = QFutureWatcher<HexGridCells>;

class EditorWindow;


class AsyncMapWorker : public QObject
{
    Q_OBJECT

    HexGridWatcher  * m_watcher;

    EditorWindow    * m_editor;

    bool              m_isRunning;


public:

    explicit AsyncMapWorker(EditorWindow * window, QObject * parent = nullptr);

    ~AsyncMapWorker();


    void startGeneration(const QSize & mapSize, bool isRotate);

    void cancelGeneration();

signals:

    void generationStarted();

    void generationFinished();

    void generationCanceled();


private slots:
    void handleGenerationFinished();
};

