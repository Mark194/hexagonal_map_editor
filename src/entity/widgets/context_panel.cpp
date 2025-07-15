#include "context_panel.hpp"

#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>

ContextPanel::ContextPanel(QWidget * parent)
    : QWidget{ parent, Qt::Popup }
{
    setWindowFlags( Qt::Popup | Qt::FramelessWindowHint );

    setAttribute( Qt::WA_ShowWithoutActivating );


    auto * layout = new QVBoxLayout;
    layout->setContentsMargins( 10, 10, 10, 10 );
    layout->setSpacing( 5 );

    setLayout( layout );

    setOpacity( 0.0 );
    // resize( 200, 180 );
}

qreal ContextPanel::opacity() const
{
    return m_opacity;
}

void ContextPanel::setOpacity(qreal opacity)
{
    m_opacity = opacity;

    setWindowOpacity( opacity );
}

void ContextPanel::showNearWidget(QWidget * widget)
{
    if ( not widget )
        return;

    // Позиционируем панель рядом с виджетом
    QPoint globalPos = widget->mapToGlobal( QPoint( 0, 0 ) );
    move( globalPos.x() + widget->width() + 5, globalPos.y() );

    // Анимация появления
    auto * anim = new QPropertyAnimation( this, "opacity" );
    anim->setDuration( 150 );
    anim->setStartValue( 0.0 );
    anim->setEndValue( 0.95 );
    anim->start( QAbstractAnimation::DeleteWhenStopped );

    show();
}

void ContextPanel::addWidget(QWidget * widget) const
{
    if ( not widget )
        return;

    layout()->addWidget( widget );
}

void ContextPanel::clearContent()
{
    auto layout = this->layout();

    if ( not layout )
        return;


    QList<QLayout *> layoutsToProcess;
    layoutsToProcess.append( layout );

    while ( !layoutsToProcess.isEmpty() )
    {
        QLayout * currentLayout = layoutsToProcess.takeFirst();

        QLayoutItem * item;
        while ( ( item = currentLayout->takeAt( 0 ) ) != nullptr )
        {
            if ( QWidget * widget = item->widget() )
            {
                widget->deleteLater();
            }
            else if ( QLayout * childLayout = item->layout() )
            {
                layoutsToProcess.append( childLayout );
            }
            delete item;
        }

        if ( currentLayout != layout )
        {
            currentLayout->deleteLater();
        }
    }
}

void ContextPanel::changeOpacity(bool isChecked)
{
    if ( isChecked )
    {
        setOpacity( 100.0 );
        showNearWidget( dynamic_cast<QWidget *>(sender()) );
    }
    else
    {
        setOpacity( 0.0 );
        close();
    }
}
