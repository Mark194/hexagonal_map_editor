//
// Created by Женя on 11.06.2025.
//

#include "command_manager.hpp"

#include <qaction.h>

#include "adapter/gui_state_provider.hpp"

#include "cmds/change_color_command.hpp"
#include "cmds/change_style_command.hpp"

#include "../entity/map_style.hpp"
#include "cmds/clear_style_command.hpp"
#include "cmds/grab_color_command.hpp"

CommandManager::CommandManager(QObject * parent)
    : QObject( parent )
  , m_undoStack( new QUndoStack( parent ) )
{
    m_undoStack->setUndoLimit( 10 );

    auto * undoAction = m_undoStack->createUndoAction( parent, "Undo" );

    undoAction->setShortcut( QKeySequence::Undo );

    auto * redoAction = m_undoStack->createRedoAction( parent, "Redo" );

    redoAction->setShortcut( QKeySequence::Redo );

    const auto widget = dynamic_cast<QWidget *>(parent);

    widget->setContextMenuPolicy( Qt::ActionsContextMenu );
    widget->addAction( undoAction );
    widget->addAction( redoAction );
}

QUndoCommand * CommandManager::create(const ActionType type, QGraphicsItem * item, const QVariant & data)
{
    const auto shape = dynamic_cast<QRegularPolygon *>(item);

    switch ( type )
    {
        case ActionType::NoAction:
            return nullptr;

        case ActionType::ChangeColor:
            return new ChangeColorCommand( shape, data.value<QColor>() );

        case ActionType::ChangeStyle:
            return new ChangeStyleCommand( shape, data.value<MapStyle>() );

        case ActionType::ClearStyle:
            return new ClearStyleCommand( shape );

        case ActionType::GrabColor:
            return new GrabColorCommand( shape, data.value<IDualColorSelector *>() );
    }

    return nullptr;
}

void CommandManager::execute(QUndoCommand * cmd)
{
    m_undoStack->push( cmd );
}
