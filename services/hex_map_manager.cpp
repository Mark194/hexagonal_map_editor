#include "hex_map_manager.hpp"


#include <cmath>


#include <QPointF>


#include <entity/widgets/qregular_polygon.hpp>


HexMapManager::HexMapManager() {}

HexGridCells HexMapManager::generateCells(const QSize & size)
{
    const double radius = 25.0; // Радиус шестиугольника (половина ширины)
    const int sides = 6;        // Количество сторон (шестиугольник)


    const double apothem = radius * std::sqrt(3) / 2;

    // Рассчитываем шаги для сетки
    const double horizontalStep = 2 * apothem;
    const double verticalStep = 1.5 * radius;

    HexGridCells cells;
    cells.reserve(size.width() * size.height() * 2);

    // Начальные координаты (с отступом)
    const double startX = radius;
    const double startY = radius;

    for (int row = 0; row < size.height(); ++row)
    {
        for (int col = 0; col < size.width(); ++col)
        {
            // Смещение для нечетных рядов
            const double xOffset = (row % 2) ? apothem : 0.0;

            // Центр шестиугольника
            const double centerX = startX + col * horizontalStep + xOffset;
            const double centerY = startY + row * verticalStep;

            QPointF center(centerX, centerY);

            auto hexagon = new QRegularPolygon(sides, radius, center, M_PI / 2);

            cells.append(hexagon);
        }
    }

    return cells;
}
