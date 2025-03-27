#include "editor_window.hpp"
#include "entity/controls/zoomer.hpp"


#include <QHBoxLayout>

#include <entity/controls/mover.hpp>


EditorWindow::EditorWindow(ISubscriber * subscriber,
    QWidget *parent)
    : QMainWindow(parent), m_subscriber(subscriber)
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
    QWidget * central = new QWidget;

    setCentralWidget( central );


    QHBoxLayout * contentLayout = new QHBoxLayout( central );


    QVBoxLayout * subformsLayout = new QVBoxLayout;


    m_instruments = new InstrumentSubForm;

    m_gridSetup   = new GridSubForm;

    m_stylesView  = new StylesView;


    subformsLayout->addWidget( m_gridSetup );

    subformsLayout->addWidget( m_instruments );

    subformsLayout->addWidget( m_stylesView );


    subformsLayout->addItem( new QSpacerItem( 50, 50 ) );

    subformsLayout->setStretch( 2, 5 );

    subformsLayout->setMargin( 0 );


    m_hexView   = new HexGrid;


    contentLayout->addWidget( m_hexView,      5 );

    contentLayout->addLayout( subformsLayout, 1 );
}

void EditorWindow::createActions()
{
    Zoomer * zoomer = new Zoomer( m_hexView );

    zoomer->setModifiers( Qt::NoModifier );

    m_actions.append( zoomer );


    Mover * mover = new Mover( m_hexView );

    m_actions.append( mover );
}
