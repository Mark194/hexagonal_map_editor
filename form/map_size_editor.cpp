#include "map_size_editor.hpp"


#include <QFormLayout>
#include <QLabel>
#include <QPushButton>


MapSizeEditor::MapSizeEditor(QWidget * parent) : QDialog( parent )
{
    auto dialogLayout = new QVBoxLayout;

    dialogLayout->addLayout( createForm() );

    dialogLayout->addLayout( createActions() );

    setLayout( dialogLayout );

    setFixedSize( 300, 150 );
}

QSize MapSizeEditor::mapSize() const
{
    return { m_mapWidthEditor->value(), m_mapHeightEditor->value() };
}

QLayout * MapSizeEditor::createForm()
{
    auto formLayout  = new QFormLayout;


    auto dialogLabel = new QLabel( "Введите размер карты:" );

    formLayout->addRow( dialogLabel );


    m_mapWidthEditor  = new QSpinBox( this );

    m_mapWidthEditor->setRange( 1, 1000 );


    m_mapHeightEditor = new QSpinBox( this );

    m_mapHeightEditor->setRange( 1, 1000 );


    formLayout->addRow( "Ширина:", m_mapWidthEditor );

    formLayout->addRow( "Высота:", m_mapHeightEditor );

    return formLayout;
}

QLayout * MapSizeEditor::createActions()
{
    auto actionsLayout = new QHBoxLayout;


    auto applyButton = new QPushButton( "Подтвердить", this );

    auto cancelButton = new QPushButton( "Отменить", this );


    connect( applyButton,  &QPushButton::clicked, this, &QDialog::accept );

    connect( cancelButton, &QPushButton::clicked, this, &QDialog::reject );


    actionsLayout->addWidget( applyButton );

    actionsLayout->addWidget( cancelButton );

    return actionsLayout;
}
