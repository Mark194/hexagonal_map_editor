#include "editor_window.hpp"


#include "../entity/controls/mover.hpp"
#include "../entity/controls/scene_click_handler.hpp"
#include "../entity/controls/zoomer.hpp"

#include "../entity/widgets/context_panel.hpp"
#include "../entity/widgets/dual_color_widget.hpp"
#include "../entity/widgets/toolpanel.hpp"

#include "../static/action_types.hpp"

EditorWindow::EditorWindow(ISubscriber * subscriber, QWidget * parent)
    : QMainWindow( parent )
  , m_subscriber( subscriber )
{
    createForm();

    m_menuForm = new MenuSubForm;

    setMenuBar( m_menuForm );

    createActions();
}

EditorWindow::~EditorWindow()
{
    qDeleteAll( m_actions );

    m_actions.clear();
}

void EditorWindow::createForm()
{
    auto * central = new QWidget();

    setCentralWidget( central );


    auto * contentLayout = new QHBoxLayout( central );
    auto * panel = new ToolPanel;

    m_buttonGroup = new QButtonGroup( this );

    const auto selectButton = panel->addButton( QIcon( ":/icons/cursor" ), "Выбрать" );

    selectButton->setProperty( "action_type", QVariant::fromValue( ActionType::NoAction ) );

    const auto brushButton = panel->addButton( QIcon( ":/icons/brush" ), "Кисть" );

    const auto bucketFillButton = panel->addButton( QIcon( ":/icons/bucket_fill" ), "Заливка" );

    brushButton->setProperty( "action_type", QVariant::fromValue( ActionType::ChangeColor ) );

    const auto stampButton = panel->addButton( QIcon( ":/icons/stamp" ), "Штамп" );

    stampButton->setProperty( "action_type", QVariant::fromValue( ActionType::ChangeStyle ) );

    const auto eraserButton = panel->addButton( QIcon( ":/icons/eraser" ), "Ластик" );

    eraserButton->setProperty( "action_type", QVariant::fromValue( ActionType::ClearStyle ) );

    const auto grabButton = panel->addButton( QIcon( ":/icons/pippet" ), "Пипетка" );

    grabButton->setProperty( "action_type", QVariant::fromValue( ActionType::GrabColor ) );

    m_buttonGroup->addButton( selectButton );

    m_buttonGroup->addButton( brushButton );

    m_buttonGroup->addButton( bucketFillButton );

    m_buttonGroup->addButton( stampButton );

    m_buttonGroup->addButton( eraserButton );

    m_buttonGroup->addButton( grabButton );

    panel->addSeparator();


    panel->addButton( QIcon( ":/icons/change_size" ), "Размер" );

    panel->addButton( QIcon( ":/icons/rotate" ), "Повернуть" );

    panel->addButton( QIcon( ":/icons/coordinate" ), "Координаты" );

    panel->addSeparator();


    const auto styleButton = panel->addButton( QIcon( ":/icons/styles" ), "Стили" );

    styleButton->setCheckable( true );

    m_contextPanel = new ContextPanel( this );

    connect( styleButton, &QToolButton::clicked, m_contextPanel, &ContextPanel::changeOpacity );

    panel->addSeparator();

    panel->addWidget( m_dualColorWidget = new DualColorWidget( panel ) );

    panel->collapse();


    m_hexView = new HexGrid;

    contentLayout->setMargin( 0 );

    contentLayout->setContentsMargins( 0, 0, 0, 0 );

    contentLayout->setSpacing( 0 );


    contentLayout->addWidget( panel, 1 );

    contentLayout->addWidget( m_hexView, 5 );
}

void EditorWindow::createActions()
{
    auto * zoomer = new Zoomer( m_hexView );

    zoomer->setModifiers( Qt::NoModifier );

    m_actions.append( zoomer );


    auto * mover = new Mover( m_hexView );

    m_actions.append( mover );


    auto * sceneHandler = new SceneClickHandler( m_hexView->scene(), this );

    connect( sceneHandler, &SceneClickHandler::itemClicked, m_subscriber, &ISubscriber::notifyHandleClick );

    m_actions.append( sceneHandler );
}
