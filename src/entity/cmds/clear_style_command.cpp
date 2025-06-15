//
// Created by Женя on 15.06.2025.
//

#include "clear_style_command.hpp"

ClearStyleCommand::ClearStyleCommand(QRegularPolygon * shape)
    : ChangeColorCommand( shape, Qt::transparent )
  , m_oldImage( shape->image() ) {}

void ClearStyleCommand::undo()
{
    m_shape->addImage( m_oldImage );

    ChangeColorCommand::undo();
}

void ClearStyleCommand::redo()
{
    m_shape->clearImage();

    ChangeColorCommand::redo();
}
