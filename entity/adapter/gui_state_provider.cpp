#include "gui_state_provider.hpp"


#include <QGraphicsItemGroup>


#include <entity/widgets/qregular_polygon.hpp>


GuiStateProvider::GuiStateProvider() {}

void GuiStateProvider::createRelations(EditorWindow * window)
{
    connect( window->m_menuForm->m_createMap, &QAction::triggered,
             window->m_subscriber,            &ISubscriber::notifyCreateMap );
}

void GuiStateProvider::loadCells(
    EditorWindow * window,
    const HexGridCells & cells)
{
    QGraphicsItemGroup * groupCells = new QGraphicsItemGroup;

    auto graphicsScene = window->m_hexView->scene();

    graphicsScene->blockSignals( true );

    graphicsScene->addItem( groupCells );


    for ( auto cell : cells )

        groupCells->addToGroup( cell );

    graphicsScene->blockSignals( false );
}

void GuiStateProvider::clearCells(EditorWindow * window)
{
    auto graphicsScene = window->m_hexView->scene();

    QList<QGraphicsItemGroup *> groups;

    for (QGraphicsItem* item : graphicsScene->items())

        if (item->type() == QGraphicsItemGroup::Type)

            groups.append(static_cast<QGraphicsItemGroup*>(item));

    qDeleteAll( groups );
}
