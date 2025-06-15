//
// Created by Женя on 11.06.2025.
//

#pragma once


#include <QGraphicsItem>
#include <QUndoStack>


#include "../static/action_types.hpp"


class CommandManager : public QObject
{
public:
    explicit CommandManager(QObject * parent = nullptr);

    static QUndoCommand * create(ActionType type, QGraphicsItem * item, const QVariant & data = QVariant());

    void execute(QUndoCommand * cmd);

private:
    QUndoStack * m_undoStack;
};
