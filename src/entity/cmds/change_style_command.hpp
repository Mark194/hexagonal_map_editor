//
// Created by Женя on 15.06.2025.
//

#pragma once


#include "change_color_command.hpp"


#include "../map_style.hpp"


class ChangeStyleCommand final : public ChangeColorCommand
{
public:
    ChangeStyleCommand(QRegularPolygon * shape, MapStyle style);

    void undo() override;

    void redo() override;

private:
    MapStyle m_style;

    QString m_oldImage;
};
