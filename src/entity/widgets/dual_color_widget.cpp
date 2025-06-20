//
// Created by Женя on 11.06.2025.
//

#include "dual_color_widget.hpp"

#include <QApplication>
#include <QColorDialog>
#include <QMouseEvent>
#include <QStyle>
#include <QVBoxLayout>

const char * FRAME_STYLE = "background-color: %1; border: 1px solid #000;";

DualColorWidget::DualColorWidget(QWidget * parent)
    : QWidget( parent )
  , m_primaryColor( Qt::white )
  , m_secondaryColor( Qt::black )
{
    setupUi();

    m_primaryColorFrame->installEventFilter( this );

    m_secondaryColorFrame->installEventFilter( this );


    connect( m_swapButton, &QPushButton::clicked, this, &DualColorWidget::swapColors );
}

void DualColorWidget::swapColors()
{
    std::swap( m_primaryColor, m_secondaryColor );

    updateColors();
}

void DualColorWidget::selectPrimaryColor() { selectColor( m_primaryColor, "Primary color" ); }

void DualColorWidget::selectSecondaryColor() { selectColor( m_secondaryColor, "Secondary color" ); }

void DualColorWidget::setPrimaryColor(const QColor & color)
{
    m_primaryColor = color;

    updateColors();
}

QColor DualColorWidget::primaryColor() const { return m_primaryColor; }

void DualColorWidget::setSecondaryColor(const QColor & color)
{
    m_secondaryColor = color;

    updateColors();
}

QColor DualColorWidget::secondaryColor() const { return m_secondaryColor; }

bool DualColorWidget::eventFilter(QObject * obj, QEvent * event)
{
    if ( event->type() == QEvent::MouseButtonPress )
    {
        if ( obj == m_primaryColorFrame )
        {
            selectPrimaryColor();
            return true;
        }
        if ( obj == m_secondaryColorFrame )
        {
            selectSecondaryColor();
            return true;
        }
    }

    return QWidget::eventFilter( obj, event );
}

void DualColorWidget::setupUi()
{
    auto * mainLayout = new QVBoxLayout( this );
    mainLayout->setSpacing( 5 );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );

    auto * colorContainer = new QWidget();
    colorContainer->setFixedSize( 30, 30 );

    m_secondaryColorFrame = new QFrame( colorContainer );
    m_primaryColorFrame = new QFrame( colorContainer );

    m_secondaryColorFrame->setFixedSize( 20, 20 );
    m_secondaryColorFrame->move( 10, 10 );

    m_primaryColorFrame->setFixedSize( 20, 20 );
    m_primaryColorFrame->move( 0, 0 );

    m_swapButton = new QPushButton();
    m_swapButton->setFixedSize( 20, 20 );
    m_swapButton->setIcon( QApplication::style()->standardIcon( QStyle::SP_ArrowRight ) );
    m_swapButton->setFlat( true );

    mainLayout->addWidget( m_swapButton, 0, Qt::AlignCenter );
    mainLayout->addWidget( colorContainer );

    updateColors();
}

void DualColorWidget::updateColors() const
{
    m_primaryColorFrame->setStyleSheet( QString( FRAME_STYLE ).arg( m_primaryColor.name() ) );

    m_secondaryColorFrame->setStyleSheet( QString( FRAME_STYLE ).arg( m_secondaryColor.name() ) );

    m_primaryColorFrame->raise();
}

void DualColorWidget::selectColor(QColor & color, const QString & title)
{
    if ( const auto newColor = QColorDialog::getColor( color, this, title ); newColor.isValid() )
    {
        color = newColor;
        updateColors();
    }
}
