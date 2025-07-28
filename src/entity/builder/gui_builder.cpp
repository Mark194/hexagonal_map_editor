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

QToolButton * GuiBuilder::createToolButton(const QString & text, const QString & iconPath, ActionType action)
{
    auto * button = new QToolButton;
    button->setIcon( QIcon( iconPath ) );
    button->setToolTip( text );
    button->setIconSize( QSize( 30,
                                30 ) );
    button->setAutoRaise( true );
    button->setCheckable( true );
    button->setAutoExclusive( true );
    button->setStyleSheet( "QToolButton { border: none; text-align: left; }" );

    button->setProperty( "action_type",
                         QVariant::fromValue( action ) );

    button->setText( text );
    button->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );

    return button;
}
