//
// Created by Женя on 14.06.2025.
//

#include "style_widget_group.hpp"

#include "style_widget.hpp"

StyleWidgetGroup::StyleWidgetGroup(QWidget * parent)
    : QWidget( parent ) {}

void StyleWidgetGroup::addWidget(StyleWidget * styleWidget)
{
    m_styleWidgets.append( styleWidget );

    connect( styleWidget,
             &StyleWidget::clicked,
             this,
             &StyleWidgetGroup::changeSelectedWidget );
}

void StyleWidgetGroup::setSelectedWidget(StyleWidget * styleWidget)
{
    m_selectedWidget = styleWidget;
}

StyleWidget * StyleWidgetGroup::selectedWidget() const
{
    return m_selectedWidget;
}

void StyleWidgetGroup::clearSelection()
{
    m_selectedWidget->blockSignals( true );

    m_selectedWidget->setSelected( false );

    m_selectedWidget->blockSignals( false );

    m_selectedWidget = nullptr;
}

void StyleWidgetGroup::changeSelectedWidget()
{
    auto selectedWidget = dynamic_cast<StyleWidget *>(sender());

    if ( not selectedWidget )
        return;

    if ( m_selectedWidget == selectedWidget or not selectedWidget->isSelected() )
        return;

    setSelectedWidget( selectedWidget );

    for ( const auto styleWidget : m_styleWidgets )
    {
        styleWidget->blockSignals( true );

        if ( styleWidget != m_selectedWidget )
            styleWidget->setSelected( false );

        styleWidget->blockSignals( false );
    }
}
