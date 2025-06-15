//
// Created by Женя on 15.06.2025.
//

#pragma once
#include "change_color_command.hpp"


class ClearStyleCommand : public ChangeColorCommand
{
public:
    explicit ClearStyleCommand(QRegularPolygon * shape);

    void undo() override;

    void redo() override;

private:
    QString m_oldImage;
};
