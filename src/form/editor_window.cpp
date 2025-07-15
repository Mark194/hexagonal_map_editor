#include "editor_window.hpp"


#include <QApplication>


#include "../entity/controls/mover.hpp"
#include "../entity/controls/scene_click_handler.hpp"
#include "../entity/controls/zoomer.hpp"

#include "../entity/widgets/collapsible_panel.hpp"
#include "../entity/widgets/dual_color_widget.hpp"
#include "../entity/widgets/toolpanel.hpp"

#include "../entity/builder/gui_builder.hpp"

#include "../static/action_types.hpp"

EditorWindow::EditorWindow(ISubscriber * subscriber, QWidget * parent)
    : QMainWindow( parent )
  , m_subscriber( subscriber )
  , m_buttonGroup( new QButtonGroup( this ) )
{
    connect( m_buttonGroup,
             qOverload<QAbstractButton *>( &QButtonGroup::buttonClicked ),
             this,
             &EditorWindow::changeCursor );

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


    const auto selectButton = GuiBuilder::createToolButton( panel,
                                                            "Выбрать",
                                                            ":/icons/cursor",
                                                            ActionType::NoAction );

    const auto brushButton = GuiBuilder::createToolButton( panel,
                                                           "Кисть",
                                                           ":/icons/brush",
                                                           ActionType::ChangeColor );

    const auto bucketFillButton = GuiBuilder::createToolButton( panel,
                                                                "Заливка",
                                                                ":/icons/bucket_fill",
                                                                ActionType::FillColor );

    const auto stampButton = GuiBuilder::createToolButton( panel,
                                                           "Штамп",
                                                           ":/icons/stamp",
                                                           ActionType::ChangeStyle );


    const auto eraserButton = GuiBuilder::createToolButton( panel,
                                                            "Ластик",
                                                            ":/icons/eraser",
                                                            ActionType::ClearStyle );


    const auto grabButton = GuiBuilder::createToolButton( panel,
                                                          "Пипетка",
                                                          ":/icons/pippet",
                                                          ActionType::GrabColor );


    m_buttonGroup->addButton( selectButton );

    m_buttonGroup->addButton( brushButton );

    m_buttonGroup->addButton( bucketFillButton );

    m_buttonGroup->addButton( stampButton );

    m_buttonGroup->addButton( eraserButton );

    m_buttonGroup->addButton( grabButton );

    panel->addSeparator();


    panel->addButton( QIcon( ":/icons/change_size" ),
                      "Размер" );

    panel->addButton( QIcon( ":/icons/rotate" ),
                      "Повернуть" );

    panel->addButton( QIcon( ":/icons/coordinate" ),
                      "Координаты" );

    panel->addSeparator();


    m_stylePanel = new CollapsiblePanel( panel,
                                         QIcon( ":/icons/styles" ),
                                         "Стили" );

    // const auto styleButton = panel->addButton( QIcon( ":/icons/styles" ),
    //                                            "Стили" );
    //
    // styleButton->setCheckable( true );

    // m_contextPanel = new ContextPanel( this );
    //
    // connect( styleButton,
    //          &QToolButton::clicked,
    //          m_contextPanel,
    //          &ContextPanel::changeOpacity );


    m_buildingPanel = new CollapsiblePanel( panel,
                                            QIcon( ":/icons/house" ),
                                            "Постройки" );

    panel->addSeparator();

    panel->addWidget( m_dualColorWidget = new DualColorWidget( panel ) );

    panel->collapse();


    m_hexView = new HexGrid;

    contentLayout->setMargin( 0 );

    contentLayout->setContentsMargins( 0,
                                       0,
                                       0,
                                       0 );

    contentLayout->setSpacing( 0 );


    contentLayout->addWidget( panel,
                              1 );

    contentLayout->addWidget( m_hexView,
                              5 );
}

void EditorWindow::createActions()
{
    auto * zoomer = new Zoomer( m_hexView );

    zoomer->setModifiers( Qt::NoModifier );

    m_actions.append( zoomer );


    auto * mover = new Mover( m_hexView );

    m_actions.append( mover );


    auto * sceneHandler = new SceneClickHandler( m_hexView->scene(),
                                                 this );

    connect( sceneHandler,
             &SceneClickHandler::itemClicked,
             m_subscriber,
             &ISubscriber::notifyHandleClick );

    m_actions.append( sceneHandler );
}

void EditorWindow::changeCursor(QAbstractButton * button)
{
    if ( not button )
        return;

    auto buttonIcon = button->icon();

    if ( buttonIcon.isNull() )
    {
        m_hexView->setCursor( Qt::ArrowCursor );
    }
    else
    {
        const auto cursorRed = QCursor( buttonIcon.pixmap( buttonIcon.actualSize( { 30, 30 } ) ),
                                        0,
                                        0 );
        m_hexView->setCursor( cursorRed );
    }
}
