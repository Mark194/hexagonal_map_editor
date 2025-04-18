#include "hex_map_manager.hpp"

#pragma omp parallel for

#include <cmath>


#include <QPointF>


#include <entity/widgets/qregular_polygon.hpp>


HexMapManager::HexMapManager() {}

HexGridCells HexMapManager::generateCells(const QSize & gridSize, bool isRotate)
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
    cells.reserve(gridSize.width() * gridSize.height());

    const int rows = isRotate ? gridSize.height() : gridSize.width();
    const int cols = isRotate ? gridSize.width() : gridSize.height();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = radius + j * p.xStep + (i % 2) * p.xOffset;
            float y = radius + i * p.yStep + (j % 2) * p.yOffset;
            cells.append(new QRegularPolygon(6, radius, QPointF(x,y), p.angle));
        }
    }

    return cells;
}
