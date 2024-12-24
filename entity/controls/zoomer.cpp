#include "zoomer.hpp"

#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QtMath>


Zoomer::Zoomer(QGraphicsView * view) : QObject( view ), m_view{view}
{
    m_view->viewport()->installEventFilter( this );

    m_view->setMouseTracking( true );

    m_modifiers = Qt::ControlModifier;

    m_baseZoomFactor = 1.0015;
}

void Zoomer::setBaseZoomFactor(double baseZoomFactor)
{
    m_baseZoomFactor = baseZoomFactor;
}

void Zoomer::setModifiers(const Qt::KeyboardModifiers & modifiers)
{
    m_modifiers = modifiers;
}


void Zoomer::gentleZoom(double factor)
{
    m_view->scale( factor, factor );

    m_view->centerOn( m_targetScenePos );

    QPointF viewport( m_view->viewport()->width()  / 2.0,
                      m_view->viewport()->height() / 2.0  );

    QPointF deltaViewportPos = m_targetViewportPos - viewport;


    auto viewportCenter = m_view->mapFromScene( m_targetScenePos ) - deltaViewportPos;

    m_view->centerOn( m_view->mapToScene( viewportCenter.toPoint() ) );

    emit zoomed();
}

bool Zoomer::eventFilter(QObject * object, QEvent * event)
{
    Q_UNUSED( object )

    switch( event->type() )
    {
        case QEvent::MouseMove:
        {
            QMouseEvent * mouseEvent = static_cast<QMouseEvent *>( event );

            QPointF delta = m_targetViewportPos - mouseEvent->pos();

            if ( qAbs( delta.x() ) > 5 or qAbs( delta.y() ) > 5 )
            {
                m_targetViewportPos = mouseEvent->pos();

                m_targetScenePos = m_view->mapToScene( mouseEvent->pos() );
            }

            break;
        }

        case QEvent::Wheel:
        {
            QWheelEvent * wheelEvent = static_cast<QWheelEvent *>( event );

            if ( QApplication::keyboardModifiers() != m_modifiers or

                 wheelEvent->orientation() != Qt::Vertical)

                return false;

            double angle = wheelEvent->angleDelta().y();

            double factor = qPow( m_baseZoomFactor, angle );

            gentleZoom( factor );

            return true;
        }

        default: return false;
    }

    return false;
}

