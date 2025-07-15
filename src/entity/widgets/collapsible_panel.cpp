//
// Created by Женя on 13.07.2025.
//

#include "collapsible_panel.hpp"

#include "dual_color_widget.hpp"
#include "../builder/gui_builder.hpp"


CollapsiblePanel::CollapsiblePanel(ToolPanel * panel, const QIcon & icon, const QString & text)
    : QWidget( panel )
{
    m_controlButton = panel->addButton( icon,
                                        text );

    m_controlButton->setCheckable( true );


    m_contextPanel = new ContextPanel( this );


    connect( m_controlButton,
             &QToolButton::clicked,
             m_contextPanel,
             &ContextPanel::changeOpacity );
}

void CollapsiblePanel::addWidget(QWidget * widget)
{
    m_contextPanel->addWidget( widget );
}

void CollapsiblePanel::clearContent()
{
    m_contextPanel->clearContent();
}
