#pragma once


#include <entity/widgets/hexgrid.hpp>
#include <entity/widgets/qregular_polygon.hpp>

#include <form/editor_window.hpp>

#include <worker/async_map_worker.hpp>

#include "interfaces/isubscriber.hpp"

#include "static/project_types.hpp"


class Regulatory : public ISubscriber
{
    EditorWindow * m_editor;

    AsyncMapWorker  * m_worker;

public:

    Regulatory();

    ~Regulatory();

    void run();

    // ISubscriber interface

    void notifyCreateMap();

    void notifySaveMap();

    void notifyQuit();

private:

    QList<QRegularPolygon *> create(int rows, int columns);

    void createCoords(QList<QRegularPolygon *> & polygons, int columns);

    void loadStyles( QList<QRegularPolygon *> & polygons, MapDict & config, StylesDict styles );

    void saveToFile();

    void saveToSvg();

};
