#include "mover.hpp"


#include <QEvent>
#include <QMouseEvent>


Mover::Mover(QGraphicsView * view) : QObject{view}, m_view{view}
{
    m_view->viewport()->installEventFilter( this );

    m_view->setMouseTracking( true );

    m_view->setTransformationAnchor( QGraphicsView::NoAnchor );
}

#include <QDebug>

bool Mover::eventFilter(QObject * watched, QEvent * event)
{
    Q_UNUSED( watched )

    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent * mouseEvent = static_cast<QMouseEvent *>( event );

            m_originX = mouseEvent->x();

            m_originY = mouseEvent->y();

            m_pressedButtons = mouseEvent->buttons();

            break;
        }

        case QEvent::MouseButtonRelease:
        {
            m_pressedButtons = Qt::NoButton;

            return true;
        }

        case QEvent::MouseMove:
        {
            QMouseEvent * mouseEvent = static_cast<QMouseEvent *>( event );

            if ( not (m_pressedButtons & Qt::MiddleButton) ) return false;


            QPointF pointOld = m_view->mapToScene( m_originX, m_originY );

            QPointF pointNew = m_view->mapToScene( mouseEvent->pos() );


            QPointF translation = pointNew - pointOld;

            auto rectF = m_view->sceneRect();

            rectF.translate( { translation.x(), translation.y() } );

            m_view->setSceneRect( rectF );

            m_originX = mouseEvent->x();

            m_originY = mouseEvent->y();

            return true;


            // return false;
        }

        default: return false;
    }

    return false;
}
