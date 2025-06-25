#include "color_selector.hpp"

#include <QColorDialog>
#include <QEvent>


const char * COLOR_FRAME_STYLE = "background-color: %1; border: 1px solid #000;";


ColorSelector::ColorSelector(QWidget * parent)
    : QFrame( parent )
{
    setFixedSize( 35,
                  35 );

    setSelectedColor( Qt::red );

    setMouseTracking( true );

    installEventFilter( this );
}

void ColorSelector::selectColor()
{
    if ( const auto color = QColorDialog::getColor( m_selectedColor,
                                                    dynamic_cast<QWidget *>(parent()),
                                                    m_title ); color.isValid() )
    {
        m_selectedColor = color;
        updateColor();
    }
}

void ColorSelector::updateColor()
{
    setStyleSheet( QString( COLOR_FRAME_STYLE ).arg( m_selectedColor.name() ) );
}

bool ColorSelector::eventFilter(QObject * obj, QEvent * event)
{
    if ( event->type() == QEvent::MouseButtonPress )
    {
        selectColor();
        return true;
    }

    return QFrame::eventFilter( obj,
                                event );
}

void ColorSelector::setTitle(const QString & title)
{
    m_title = title;
}

void ColorSelector::setSelectedColor(const QColor & color)
{
    m_selectedColor = color;

    updateColor();
}

QColor ColorSelector::selectedColor()
{
    return m_selectedColor;
}
