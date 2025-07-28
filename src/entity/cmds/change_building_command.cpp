//
// Created by Женя on 28.07.2025.
//

#include "change_building_command.hpp"

ChangeBuildingCommand::ChangeBuildingCommand
(QRegularPolygon * shape, const QString & imagePath, QRegularPolygon::HexCorner corner)
    : m_shape( shape )
  , m_imagePath( imagePath )
  , m_corner( corner )
  , m_oldImagePath( shape->image( corner ) ) {}

void ChangeBuildingCommand::undo()
{
    m_shape->clearImage( m_corner );

    if ( not m_oldImagePath.isEmpty() )
        m_shape->addImage( m_oldImagePath,
                           m_corner );
}

void ChangeBuildingCommand::redo()
{
    m_shape->addImage( m_imagePath,
                       m_corner );
}
