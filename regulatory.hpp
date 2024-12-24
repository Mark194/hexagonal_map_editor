#pragma once


#include "hexgrid.hpp"
#include "qregular_polygon.hpp"


class Regulatory
{
    HexGrid * m_hexGrid;

    QObjectList m_objects;

public:
    Regulatory();

    void run();

private:

    QList<QRegularPolygon *> create(int rows, int columns);

    void createCoords(QList<QRegularPolygon *> & polygons , int columns);
};
