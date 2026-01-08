#include "clear_building_command.hpp"

ClearBuildingCommand::ClearBuildingCommand(
    QRegularPolygon * shape, QRegularPolygon::HexCorner corner ) :
    m_shape( shape ), m_corner( corner ),
    m_imagePath( m_shape->image( corner ) )
{}

void ClearBuildingCommand::redo()
{
    m_shape->clearImage( m_corner );
}

void ClearBuildingCommand::undo()
{
    m_shape->addImage( m_imagePath, m_corner );
}
