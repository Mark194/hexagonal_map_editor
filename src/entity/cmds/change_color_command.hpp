//
// Created by Женя on 11.06.2025.
//

#pragma once


#include <QUndoCommand>


#include "../widgets/qregular_polygon.hpp"


class ChangeColorCommand : public QUndoCommand
{
public:
    ChangeColorCommand(QRegularPolygon * shape, QColor color);

    void undo() override;

    void redo() override;

protected:
    QRegularPolygon * m_shape;

    QColor m_color;

    QColor m_oldColor;
};
