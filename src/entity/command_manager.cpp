//
// Created by Женя on 11.06.2025.
//

#include "command_manager.hpp"

#include <qaction.h>

#include "adapter/gui_state_provider.hpp"

#include "cmds/change_color_command.hpp"

// #include "adapter/presenter_state_provider.hpp"
#include "adapter/regulatory_state_provider.hpp"
#include "cmds/change_style_command.hpp"
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

QUndoCommand * CommandManager::create(const ActionType type, QGraphicsItem * item, EditorWindow * editorWindow)
{
    const auto shape = dynamic_cast<QRegularPolygon *>(item);

    switch ( type )
    {
        case ActionType::NoAction:
            return nullptr;

        case ActionType::ChangeColor:
        {
            const QColor color = GuiStateProvider::primaryColor( editorWindow );
            return new ChangeColorCommand( shape, color );
        }

        case ActionType::ChangeStyle:
            return createCommandChangeStyle( shape, editorWindow );

        case ActionType::ClearStyle:
            return new ClearStyleCommand( shape );

        case ActionType::GrabColor:
        {
            const auto colorSelector = GuiStateProvider::colorSelector( editorWindow );

            return new GrabColorCommand( shape, colorSelector );
        }

        default:
            return nullptr;
    }
}

void CommandManager::execute(QUndoCommand * cmd)
{
    m_undoStack->push( cmd );
}

QUndoCommand * CommandManager::createCommandChangeStyle(QRegularPolygon * shape, EditorWindow * editorWindow)
{
    try
    {
        const auto selectedStyleName = GuiStateProvider::selectedStyle( editorWindow );

        const auto subscriber = GuiStateProvider::subscriber( editorWindow );

        const auto selectedStyle = RegulatoryStateProvider::mapStyle( subscriber, selectedStyleName );

        if ( not selectedStyle.isValid() )
            throw std::logic_error( "unknown style" );

        return new ChangeStyleCommand( shape, selectedStyle );
    }
    catch ( [[maybe_unused]] const std::logic_error & err )
    {
        return nullptr;
    }
}
