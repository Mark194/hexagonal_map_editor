#include "gui_state_provider.hpp"

#include <qgridlayout.h>


#include "../../services/hex_map_manager.hpp"
#include "../widgets/qregular_polygon.hpp"
#include "../widgets/style_widget.hpp"
#include "../widgets/style_widget_group.hpp"


class StyleWidgetGroup;

GuiStateProvider::GuiStateProvider() = default;

GuiStateProvider::~GuiStateProvider() = default;

void GuiStateProvider::createRelations(EditorWindow * window)
{
    auto menuForm = window->m_menuForm;

    connect( menuForm->m_createMap,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifyCreateMap );

    connect( menuForm->m_openMap,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifyOpenMap );

    connect( menuForm->m_saveMap,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifySaveMap );

    connect( menuForm->m_quit,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifyQuit );

    connect( menuForm->m_addStyle,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifyLoadStyles );

    connect( menuForm->m_createStyle,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifyCreateStyle );

    connect( menuForm->m_changeStyle,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifyChangeStyle );

    connect( menuForm->m_saveStyle,
             &QAction::triggered,
             window->m_subscriber,
             &ISubscriber::notifySaveStyles );
}

void GuiStateProvider::loadCells(QGraphicsScene * graphicsScene, const HexGridCells & cells)
{
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

    for ( QGraphicsItem * item : graphicsScene->items() )

        if ( item->type() == QGraphicsItemGroup::Type )

            groups.append( dynamic_cast<QGraphicsItemGroup *>(item) );

    qDeleteAll( groups );
}

void GuiStateProvider::loadCoords(const HexGridCells & cells, const QStringList & coords)
{
    for ( int i = 0; i < cells.size(); i++ )
    {
        cells[ i ]->addText( coords.at( i ) );
        cells[ i ]->setCoord( coords.at( i ) );
    }
}

QGraphicsScene * GuiStateProvider::scene(const EditorWindow * window)
{
    return window->m_hexView->scene();
}


void GuiStateProvider::loadStylesMiniatures(const EditorWindow * window, const StylesDict & styles)
{
    window->m_stylePanel->clearContent();


    auto * scrollArea = new QScrollArea( window->m_stylePanel );

    scrollArea->setWidgetResizable( true );
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    auto contentWidget = new QWidget();

    scrollArea->setWidget( contentWidget );

    auto * layout = new QGridLayout( contentWidget );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );
    layout->setHorizontalSpacing( 0 );
    layout->setVerticalSpacing( 0 );
    layout->setContentsMargins( 0,
                                0,
                                0,
                                0 );

    int i = 0;

    const auto group = new StyleWidgetGroup( const_cast<EditorWindow *>(window) );

    group->setObjectName( "styleGroup" );

    for ( auto it = styles.begin(); it != styles.end(); ++it )
    {
        const auto styleWidget = new StyleWidget( it.key(),
                                                  it.value().color,
                                                  it.value().image );

        const int row = i / 2;
        const int col = i % 2;

        layout->addWidget( styleWidget,
                           row,
                           col,
                           Qt::AlignCenter );

        group->addWidget( styleWidget );

        ++i;
    }

    window->m_stylePanel->addWidget( scrollArea );
}

void GuiStateProvider::loadStyles(const HexGridCells & cells, const MapDict & config, const StylesDict & styles)
{
    for ( const auto & polygon : cells )
    {
        QString polygonCoord = polygon->coord();

        auto styleCoord = config[ polygonCoord ];

        if ( styleCoord.style == "default" )
            continue;
        auto styleMap = styles.value( styleCoord.style );
        if ( styleCoord.customColor.isEmpty() )
            polygon->setColor( styleMap.color );
        else

            polygon->setColor( styleCoord.customColor );

        polygon->addImage( styleMap.image );
    }
}

void GuiStateProvider::loadBuildingsMiniatures(const EditorWindow * window, const BuildingsDict & config)
{
    window->m_buildingPanel->clearContent();

    auto * scrollArea = new QScrollArea( window->m_buildingPanel );

    scrollArea->setWidgetResizable( true );
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    auto contentWidget = new QWidget();

    scrollArea->setWidget( contentWidget );

    auto * layout = new QGridLayout( contentWidget );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );
    layout->setHorizontalSpacing( 0 );
    layout->setVerticalSpacing( 0 );
    layout->setContentsMargins( 0,
                                0,
                                0,
                                0 );

    int i = 0;

    const auto group = new StyleWidgetGroup( const_cast<EditorWindow *>(window) );

    group->setObjectName( "styleGroup" );

    for ( auto it = config.begin(); it != config.end(); ++it )
    {
        const auto styleWidget = new StyleWidget( it.key(),
                                                  Qt::transparent,
                                                  it.value().imagePath );

        const int row = i / 2;
        const int col = i % 2;

        layout->addWidget( styleWidget,
                           row,
                           col,
                           Qt::AlignCenter );

        group->addWidget( styleWidget );

        ++i;
    }

    window->m_buildingPanel->addWidget( scrollArea );
}

ActionType GuiStateProvider::actionType(const EditorWindow * window)
{
    auto checkedButton = window->m_buttonGroup->checkedButton();

    if ( not checkedButton )
        return ActionType::NoAction;

    return checkedButton->property( "action_type" ).value<ActionType>();
}

QColor GuiStateProvider::primaryColor(const EditorWindow * window)
{
    return window->m_dualColorWidget->primaryColor();
}

QWidget * GuiStateProvider::hexView(const EditorWindow * window)
{
    return window->m_hexView;
}

QString GuiStateProvider::selectedStyle(const EditorWindow * window)
{
    const auto styleGroup = window->findChild<StyleWidgetGroup *>( "styleGroup" );

    if ( not styleGroup )
        throw std::logic_error( "no style group found" );

    if ( auto selectedWidget = styleGroup->selectedWidget() )
        return selectedWidget->styleName();

    throw std::logic_error( "no style selected" );
}

IDualColorSelector * GuiStateProvider::colorSelector(const EditorWindow * window)
{
    return window->m_dualColorWidget;
}

ISubscriber * GuiStateProvider::subscriber(const EditorWindow * window)
{
    return window->m_subscriber;
}

HexGridCells GuiStateProvider::polygons(const EditorWindow * window)
{
    auto group = findGroup( window->m_hexView->scene() );

    auto items = group->childItems();

    HexGridCells cells;

    for ( auto item : items )
        if ( auto polygon = dynamic_cast<QRegularPolygon *>(item) )
            cells.append( polygon );

    return cells;
}

StylesDict GuiStateProvider::styles(const EditorWindow * window)
{
    const auto styleGroup = window->findChild<StyleWidgetGroup *>( "styleGroup" );

    auto styleWidgets = styleGroup->styleWidgets();

    StylesDict styles;

    for ( auto styleWidget : styleWidgets )

        styles[ styleWidget->styleName() ] = { styleWidget->color().name(), styleWidget->imagePath() };


    return styles;
}

QGraphicsItemGroup * GuiStateProvider::findGroup(const QGraphicsScene * scene)
{
    for ( QGraphicsItem * item : scene->items() )
    {
        if ( item->type() == QGraphicsItemGroup::Type )
        {
            return dynamic_cast<QGraphicsItemGroup *>(item);
        }
    }

    return nullptr;
}
