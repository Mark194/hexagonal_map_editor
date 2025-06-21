//
// Created by Женя on 21.06.2025.
//

#pragma once


#include "change_color_command.hpp"


#include "../../static/types.hpp"


class FillColorCommand final : public ChangeColorCommand
{
public:
    FillColorCommand(QRegularPolygon * shape, const QColor & color, const HexGridCells & polygons);

    void undo() override;

    void redo() override;

private:
    HexGridCells m_adjacentPolygons;

    static HexGridCells findMatchingPolygons(QRegularPolygon * current, const HexGridCells & polygons);
};
