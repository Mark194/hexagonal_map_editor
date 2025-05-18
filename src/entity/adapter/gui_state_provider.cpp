#include "gui_state_provider.hpp"


#include "../widgets/qregular_polygon.hpp"


GuiStateProvider::GuiStateProvider() = default;

GuiStateProvider::~GuiStateProvider() = default;

void GuiStateProvider::createRelations(EditorWindow * window)
{
    connect( window->m_menuForm->m_createMap, &QAction::triggered,
             window->m_subscriber,            &ISubscriber::notifyCreateMap );

    connect( window->m_menuForm->m_openMap, &QAction::triggered,
             window->m_subscriber,            &ISubscriber::notifyOpenMap );

    connect( window->m_menuForm->m_saveMap,   &QAction::triggered,
             window->m_subscriber,            &ISubscriber::notifySaveMap );

    connect( window->m_menuForm->m_quit,      &QAction::triggered,
             window->m_subscriber,            &ISubscriber::notifyQuit );
}

void GuiStateProvider::loadCells(
    EditorWindow * window,
    const HexGridCells & cells)
{

    auto graphicsScene = window->m_hexView->scene();


    auto * groupCells = new QGraphicsItemGroup;

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

            groups.append(dynamic_cast<QGraphicsItemGroup*>(item));

    qDeleteAll( groups );
}

void GuiStateProvider::loadCoords(const HexGridCells & cells, const QStringList & coords)
{
    for ( int i = 0; i < cells.size(); i++ )

        cells[i]->addText( coords.at( i ) );
}

QGraphicsScene * GuiStateProvider::scene(const EditorWindow * window)
{
    return window->m_hexView->scene();
}
