#pragma once


#include <QSize>


#include "../static/types.hpp"


class HexMapManager
{
public:
    HexMapManager();

    static HexGridCells generateCells(const QSize & size, bool isRotate = true);

    static QStringList generateCoord(const QSize & size);
};

