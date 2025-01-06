#include "gui_builder.hpp"

GuiBuilder::GuiBuilder() {}

QPushButton * GuiBuilder::createButton(QString iconPath)
{
    QPushButton * button = new QPushButton;

    button->setFlat( true );

    button->setIcon( QIcon( iconPath ) );

    button->setIconSize( { 30, 30 } );

    return button;
}
