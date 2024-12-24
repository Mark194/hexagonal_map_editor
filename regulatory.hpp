#pragma once


#include <entity/widgets/hexgrid.hpp>
#include <entity/widgets/qregular_polygon.hpp>

#include "static/project_types.hpp"


class Regulatory
{
    HexGrid * m_hexGrid;

    QObjectList m_objects;

public:
    Regulatory();

    void run();

private:

    QList<QRegularPolygon *> create(int rows, int columns);

    void createCoords(QList<QRegularPolygon *> & polygons, int columns);

    void loadStyles( QList<QRegularPolygon *> & polygons, MapDict & config, StylesDict styles );

    void saveToFile();
};
