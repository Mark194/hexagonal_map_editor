#include "grid_sub_form.hpp"

#include <QGroupBox>
#include <QVBoxLayout>

#include <entity/builder/gui_builder.hpp>

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


    QGridLayout * actionLayout = new QGridLayout;

    instrumentBox->setLayout( actionLayout );


    auto changeSizeButton = GuiBuilder::createButton( ":/icons/change_size" );

    actionLayout->addWidget( changeSizeButton, 0, 0 );


    auto rotateButton = GuiBuilder::createButton( ":/icons/rotate" );

    actionLayout->addWidget( rotateButton, 0, 1 );


    auto coordinateButton = GuiBuilder::createButton( ":/icons/coordinate" );

    actionLayout->addWidget( coordinateButton, 0, 2 );
}
