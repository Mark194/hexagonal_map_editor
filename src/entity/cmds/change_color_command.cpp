//
// Created by Женя on 11.06.2025.
//

#include "change_color_command.hpp"

#include <QBrush>
#include <utility>

ChangeColorCommand::ChangeColorCommand(QRegularPolygon * shape, QColor color)
    : m_shape( shape )
  , m_color( std::move( color ) )
  , m_oldColor( shape->brush().color() )
{
    if ( m_oldColor == Qt::black )
        m_oldColor = Qt::transparent;
}

void ChangeColorCommand::undo()
{
    if ( m_oldColor.isValid() )

        m_shape->setColor( m_oldColor );
    else
        m_shape->setColor( Qt::transparent );
}

void ChangeColorCommand::redo()
{
    m_shape->setColor( m_color );
}
