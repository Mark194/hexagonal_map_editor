#include "style_widget.hpp"

#include <cmath>
#include <QHelpEvent>
#include <qfileinfo.h>
#include <QLabel>
#include <QPainter>
#include <QSvgWidget>
#include <QToolTip>
#include <QVBoxLayout>


class QHelpEvent;

StyleWidget::StyleWidget(const QString & styleName, const QColor & color, const QString & imagePath, QWidget * parent)
    : QWidget( parent )
  , m_styleName( styleName )
  , m_color( color )
{
    setFixedSize( 60, 60 );
    setWindowFlags( windowFlags() | Qt::FramelessWindowHint );

    setToolTip( styleName ); // Устанавливаем подсказку
    setAttribute( Qt::WA_Hover, true );

    auto * layout = new QVBoxLayout( this );
    layout->setAlignment( Qt::AlignCenter );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );


    auto iconWidget = loadIcon( imagePath );
    if ( iconWidget )
        layout->addWidget( iconWidget, 0, Qt::AlignCenter );


    setLayout( layout );
}

void StyleWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setBrush( m_color );
    painter.setPen( QPen( Qt::black, 1 ) );

    QPolygonF hexagon;
    int centerX = width() / 2;
    int centerY = height() / 2;
    int radius = qMin( width(), height() ) / 2 - 5;

    for ( int i = 0; i < 6; ++i )
    {
        double angle = 2 * M_PI * i / 6 + M_PI / 6; // Поворачиваем на 30 градусов
        hexagon << QPointF( centerX + radius * cos( angle ), centerY + radius * sin( angle ) );
    }

    painter.drawPolygon( hexagon );

    QWidget::paintEvent( event );
}

bool StyleWidget::event(QEvent * event)
{
    if ( event->type() == QEvent::ToolTip )
    {
        QToolTip::showText( static_cast<QHelpEvent *>(event)->globalPos(), m_styleName, this );
        return true;
    }

    return QWidget::event( event );
}

QWidget * StyleWidget::loadIcon(const QString & imagePath)
{
    if ( imagePath.isEmpty() )
        return nullptr;

    QFileInfo fileInfo( imagePath );

    QString suffix = fileInfo.suffix().toLower();

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
