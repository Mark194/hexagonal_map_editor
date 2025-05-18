#include "hex_map_manager.hpp"

#pragma omp parallel for

#include <cmath>


#include "../entity/widgets/qregular_polygon.hpp"


HexMapManager::HexMapManager() = default;

HexGridCells HexMapManager::generateCells(const QSize & size, const bool isRotate)
{
    constexpr float radius = 25.0f;
    constexpr float sqrt3 = 1.73205080757f; // √3
    constexpr float hexHeight = radius * 2.0f;
    constexpr float hexWidth = radius * sqrt3;

           // Параметры для обеих ориентаций
    constexpr struct {
        float xStep, yStep;
        float xOffset, yOffset;
        float angle;
    } params[2] = {
        // Вертикальная ориентация (острием вверх)
        {hexWidth, hexHeight * 0.75f, hexWidth/2, 0, M_PI_2},
        // Горизонтальная ориентация (ребром вверх)
        {hexHeight * 0.75f, hexWidth, 0, hexWidth/2, 0}
    };

    const auto& p = params[isRotate ? 1 : 0];
    HexGridCells cells;
    cells.reserve(size.width() * size.height());

    const int rows = isRotate ? size.height() : size.width();
    const int cols = isRotate ? size.width() : size.height();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = radius + j * p.xStep + (i % 2) * p.xOffset;
            float y = radius + i * p.yStep + (j % 2) * p.yOffset;
            cells.append(new QRegularPolygon(6, radius, QPointF(x,y), p.angle));
        }
    }

    return cells;
}

const char * COORD_FMT = "%1, %2";

QStringList HexMapManager::generateCoord(const QSize & size)
{
    const auto countCell = size.width() * size.width();

    QStringList coords;

    coords.reserve( countCell );

    for ( int i = 0, row = 0, count=0; i < countCell; ++i )
    {
        auto coord = QString( COORD_FMT ).arg( count ).arg( row );

        coords.append( coord );

        count++;

        if ( count >= size.height() )
        {
            row++;

            count = 0;
        }
    }

    return coords;
}
