#include "editor_window.hpp"


#include "../entity/controls/mover.hpp"
#include "../entity/controls/zoomer.hpp"

#include "../entity/widgets/context_panel.hpp"
#include "../entity/widgets/toolpanel.hpp"


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


    // QVBoxLayout * subformsLayout = new QVBoxLayout;

    auto * panel = new ToolPanel;

    panel->addButton( QIcon( ":/icons/cursor" ), "Выбрать" );

    panel->addButton( QIcon( ":/icons/brush" ), "Кисть" );

    panel->addButton( QIcon( ":/icons/bucket_fill" ), "Заливка" );

    panel->addButton( QIcon( ":/icons/stamp" ), "Штамп" );

    panel->addButton( QIcon( ":/icons/eraser" ), "Ластик" );

    panel->addButton( QIcon( ":/icons/pippet" ), "Пипетка" );


    panel->addSeparator();


    panel->addButton( QIcon( ":/icons/change_size" ), "Размер" );

    panel->addButton( QIcon( ":/icons/rotate" ), "Повернуть" );

    panel->addButton( QIcon( ":/icons/coordinate" ), "Координаты" );

    panel->addSeparator();

    auto styleButton = panel->addButton( QIcon( ":/icons/styles" ), "Стили" );

    styleButton->setCheckable( true );

    m_contextPanel = new ContextPanel( this );

    connect( styleButton, &QToolButton::clicked, m_contextPanel, &ContextPanel::changeOpacity );

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
}
