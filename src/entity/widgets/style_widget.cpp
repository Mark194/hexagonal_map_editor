#include "style_widget.hpp"

#include <cmath>
#include <qapplication.h>
#include <QFileInfo>
#include <QHelpEvent>
#include <QLabel>
#include <QPainter>
#include <QSvgWidget>
#include <QToolTip>
#include <QVBoxLayout>


StyleWidget::StyleWidget(const QString & styleName, const QColor & color, const QString & imagePath, QWidget * parent)
    : QWidget( parent )
  , m_isSelected( false )
  , m_styleName( styleName )
  , m_color( color )
{
    setFixedSize( 60, 60 );
    setWindowFlags( windowFlags() | Qt::FramelessWindowHint );

    setToolTip( styleName );
    setAttribute( Qt::WA_Hover, true );

    auto * layout = new QVBoxLayout( this );
    layout->setAlignment( Qt::AlignCenter );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );


    if ( auto iconWidget = loadIcon( imagePath ) )
        layout->addWidget( iconWidget, 0, Qt::AlignCenter );


    setLayout( layout );
}

bool StyleWidget::isSelected() const
{
    return m_isSelected;
}

void StyleWidget::setSelected(const bool selected)
{
    if ( m_isSelected != selected )
    {
        m_isSelected = selected;

        update();
    }
}

QString StyleWidget::styleName() const
{
    return m_styleName;
}

void StyleWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setBrush( m_color );

    if ( m_isSelected )
    {
        painter.setPen( QPen( palette().highlight(), 3 ) );
    }
    else
    {
        painter.setPen( QPen( Qt::black, 1 ) );
    }

    QPolygonF hexagon;
    const int centerX = width() / 2;
    const int centerY = height() / 2;
    const int radius = qMin( width(), height() ) / 2 - 5;

    for ( int i = 0; i < 6; ++i )
    {
        const double angle = 2 * M_PI * i / 6 + M_PI / 6; // Поворачиваем на 30 градусов
        hexagon << QPointF( centerX + radius * cos( angle ), centerY + radius * sin( angle ) );
    }

    painter.drawPolygon( hexagon );

    QWidget::paintEvent( event );
}

void StyleWidget::mousePressEvent(QMouseEvent * event)
{
    if ( event->button() == Qt::LeftButton )
    {
        setSelected( not m_isSelected );

        emit clicked();
    }

    QWidget::mousePressEvent( event );
}

bool StyleWidget::event(QEvent * event)
{
    if ( event->type() == QEvent::ToolTip )
    {
        QToolTip::showText( dynamic_cast<QHelpEvent *>(event)->globalPos(), m_styleName, this );
        return true;
    }
    if ( event->type() == QEvent::HoverEnter )
    {
        setCursor( Qt::PointingHandCursor );
    }
    else if ( event->type() == QEvent::HoverLeave )
    {
        setCursor( Qt::ArrowCursor );
    }

    return QWidget::event( event );
}

QWidget * StyleWidget::loadIcon(const QString & imagePath)
{
    if ( imagePath.isEmpty() )
        return nullptr;

    const QFileInfo fileInfo( imagePath );

    const QString suffix = fileInfo.suffix().toLower();

    if ( suffix == "svg" )
    {
        auto * svgIcon = new QSvgWidget( imagePath, this );
        svgIcon->setFixedSize( 32, 32 );
        return svgIcon;
    }
    if ( suffix == "png" )
    {
        auto * pixmapLabel = new QLabel( this );
        QPixmap pixmap( imagePath );

        if ( pixmap.isNull() )
            return nullptr;

        pixmap = pixmap.scaled( 40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation );
        pixmapLabel->setPixmap( pixmap );
        pixmapLabel->setFixedSize( 40, 40 );
        return pixmapLabel;
    }

    return nullptr;
}
