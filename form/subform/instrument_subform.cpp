#include "instrument_subform.hpp"
#include "entity/builder/gui_builder.hpp"


#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>


InstrumentSubForm::InstrumentSubForm(QWidget *parent) : QWidget{parent}
{
    createForm();
}

void InstrumentSubForm::createForm()
{
    QVBoxLayout * layoutForm = new QVBoxLayout;

    setLayout( layoutForm );


    QGroupBox * instrumentBox = new QGroupBox( "Инструменты" );

    instrumentBox->setAlignment( Qt::AlignHCenter );

    layoutForm->addWidget( instrumentBox );



    QGridLayout * instrumentLayout = new QGridLayout;

    instrumentBox->setLayout( instrumentLayout );


    auto selectModeButton = GuiBuilder::createButton( ":/icons/cursor" );

    instrumentLayout->addWidget( selectModeButton, 0, 0 );



    auto paintBrushButton = GuiBuilder::createButton( ":/icons/brush" );

    instrumentLayout->addWidget( paintBrushButton, 0, 1 );


    auto bucketFillButton = GuiBuilder::createButton( ":/icons/bucket_fill" );

    instrumentLayout->addWidget( bucketFillButton, 0, 2 );


    auto stampButton = GuiBuilder::createButton( ":/icons/stamp" );

    instrumentLayout->addWidget( stampButton, 1, 0 );


    auto eraserButton = GuiBuilder::createButton( ":/icons/eraser" );

    instrumentLayout->addWidget( eraserButton, 1, 1 );


    QPushButton * pippetButton = GuiBuilder::createButton( ":/icons/pippet" );

    instrumentLayout->addWidget( pippetButton, 1, 2 );
}
