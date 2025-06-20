//
// Created by Женя on 20.06.2025.
//

#pragma once


#include "change_color_command.hpp"

class IDualColorSelector;

class GrabColorCommand : public ChangeColorCommand
{
public:
    explicit GrabColorCommand(QRegularPolygon * shape, IDualColorSelector * selector);

    void undo() override;

    void redo() override;

private:
    IDualColorSelector * m_selector;
};
