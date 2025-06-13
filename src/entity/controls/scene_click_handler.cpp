//
// Created by Женя on 13.06.2025.
//

#include "scene_click_handler.hpp"


#include <QGraphicsSceneMouseEvent>


SceneClickHandler::SceneClickHandler(QGraphicsScene * scene, QObject * parent)
    : QObject( parent )
  , m_scene( scene )
{
    if ( scene )
        scene->installEventFilter( this );
}

QGraphicsItem * SceneClickHandler::currentItem() const
{
    return m_scene->itemAt( m_scenePos, QTransform() );
}

bool SceneClickHandler::eventFilter(QObject * watched, QEvent * event)
{
    if ( watched == m_scene && event->type() == QEvent::GraphicsSceneMousePress )
    {
        const auto mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent *>(event);

        m_scenePos = mouseEvent->scenePos();

        if ( m_scene->itemAt( m_scenePos, QTransform() ) )
        {
            emit itemClicked();
        }
    }

    return QObject::eventFilter( watched, event );
}
