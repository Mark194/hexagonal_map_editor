#pragma once

#include <QUndoCommand>

#include "../widgets/qregular_polygon.hpp"

class ClearBuildingCommand : public QUndoCommand
{
public:
    ClearBuildingCommand( QRegularPolygon * shape,
                          QRegularPolygon::HexCorner corner );

    void redo() override;

    void undo() override;

private:
    QRegularPolygon * m_shape;

    QString m_imagePath;

    QRegularPolygon::HexCorner m_corner;
};
