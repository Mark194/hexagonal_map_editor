//
// Created by Женя on 15.06.2025.
//

#include "change_style_command.hpp"

#include <QBrush>

#include "../widgets/qregular_polygon.hpp"


ChangeStyleCommand::ChangeStyleCommand(QRegularPolygon * shape, MapStyle style)
    : ChangeColorCommand( shape, style.color )
  , m_style( std::move( style ) )
  , m_oldImage( shape->image() ) {}

void ChangeStyleCommand::undo()
{
    m_shape->addImage( m_oldImage );

    ChangeColorCommand::undo();
}

void ChangeStyleCommand::redo()
{
    m_shape->addImage( m_style.image );

    ChangeColorCommand::redo();
}
