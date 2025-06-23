#include "gui_builder.hpp"

#include <qvariant.h>

GuiBuilder::GuiBuilder() {}

QPushButton * GuiBuilder::createButton(const QString & iconPath)
{
    auto * button = new QPushButton;

    button->setFlat( true );

    button->setIcon( QIcon( iconPath ) );

    button->setIconSize( { 30, 30 } );

    return button;
}

QToolButton * GuiBuilder::createToolButton
(ToolPanel * panel, const QString & text, const QString & iconPath, const ActionType action)
{
    const auto button = panel->addButton( QIcon( iconPath ),
                                          text );

    button->setProperty( "action_type",
                         QVariant::fromValue( action ) );

    return button;
}
