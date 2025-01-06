#include "grid_sub_form.hpp"

#include <QGroupBox>
#include <QVBoxLayout>

GridSubForm::GridSubForm(QWidget *parent) : QWidget{parent}
{
    createSubForm();
}

void GridSubForm::createSubForm()
{
    QVBoxLayout * layoutForm = new QVBoxLayout;

    setLayout( layoutForm );


    QGroupBox * instrumentBox = new QGroupBox( "Сетка" );

    instrumentBox->setAlignment( Qt::AlignHCenter );

    layoutForm->addWidget( instrumentBox );


    QPushButton * changeSizeButton = new QPushButton;
}
