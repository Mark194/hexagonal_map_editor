#pragma once


#include "static/types.hpp"


#include <QSize>


class HexMapManager
{
public:
    HexMapManager();

    static HexGridCells generateCells(const QSize & size, bool isRotate = true);
};

