#pragma once

#include <QUndoCommand>

#include "../widgets/qregular_polygon.hpp"

class ChangeBuildingCommand : public QUndoCommand
{
public:
    ChangeBuildingCommand(QRegularPolygon * shape, const QString & imagePath, QRegularPolygon::HexCorner corner);

    void undo() override;

    void redo() override;

private:
    QRegularPolygon * m_shape;

    QString m_imagePath;

    QString m_oldImagePath;

    QRegularPolygon::HexCorner m_corner;
};
