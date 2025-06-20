//
// Created by Женя on 20.06.2025.
//

#include "grab_color_command.hpp"


#include <QBrush>

#include "../../interfaces/idual_color_selector.hpp"
#include "../widgets/qregular_polygon.hpp"


GrabColorCommand::GrabColorCommand(QRegularPolygon * shape, IDualColorSelector * selector)
    : ChangeColorCommand( shape, selector->primaryColor() )
  , m_selector( selector ) {}

void GrabColorCommand::undo()
{
    m_selector->setPrimaryColor( m_oldColor );
}

void GrabColorCommand::redo()
{
    m_selector->setPrimaryColor( m_shape->brush().color() );
}
