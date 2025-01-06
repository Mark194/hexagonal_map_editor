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


    QVBoxLayout * contentLayout = new QVBoxLayout( central );


    QHBoxLayout * subformsLayout = new QHBoxLayout;


    m_instruments = new InstrumentSubForm;

    m_gridSetup   = new GridSubForm;


    subformsLayout->addWidget( m_instruments );

    subformsLayout->addWidget( m_gridSetup );


    m_hexView   = new HexGrid;


    contentLayout->addLayout( subformsLayout, 1 );

    contentLayout->addWidget( m_hexView,      5 );

}
