//
// Created by Женя on 11.06.2025.
//

#pragma once


#include <QGraphicsItem>
#include <QUndoStack>


#include "../form/editor_window.hpp"
#include "../static/action_types.hpp"
#include "widgets/qregular_polygon.hpp"


class CommandManager : public QObject
{
public:
    explicit CommandManager(QObject * parent = nullptr);

    static QUndoCommand * create(ActionType type, QGraphicsItem * item, EditorWindow * editorWindow);

    void execute(QUndoCommand * cmd);

private:
    QUndoStack * m_undoStack;

    static QUndoCommand * createCommandChangeStyle(QRegularPolygon * shape, EditorWindow * editorWindow);

    static QUndoCommand * createBuildingStyle(QRegularPolygon * shape, EditorWindow * editorWindow);
};
