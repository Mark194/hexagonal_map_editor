#include "styles_view.hpp"


#include <QGroupBox>
#include <QVBoxLayout>


StylesView::StylesView(
    QWidget *parent)
    : QWidget{parent}
{
    createForm();
}

void StylesView::createForm()
{
    QVBoxLayout * formLayout = new QVBoxLayout;

    setLayout( formLayout );


    QGroupBox * groupStyles = new QGroupBox( "Стили" );

    groupStyles->setAlignment( Qt::AlignHCenter );

    formLayout->addWidget( groupStyles );


    QVBoxLayout * groupLayout = new QVBoxLayout;

    groupStyles->setLayout( groupLayout );


    m_hexagonalView = new HexGrid;

    m_hexagonalView->setInteractive( false );

    groupLayout->addWidget( m_hexagonalView );
}


