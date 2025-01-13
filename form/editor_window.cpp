#include "editor_window.hpp"


#include <QHBoxLayout>


EditorWindow::EditorWindow(
    QWidget *parent)
    : QMainWindow(parent)
{
    createForm();
}

EditorWindow::~EditorWindow() {}

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
