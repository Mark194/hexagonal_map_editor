#pragma once


#include <QPushButton>

#include "../../static/action_types.hpp"
#include "../widgets/toolpanel.hpp"


class GuiBuilder
{
public:
    GuiBuilder();

    static QPushButton * createButton(const QString & iconPath);

    static QToolButton * createToolButton
    (ToolPanel * panel, const QString & text, const QString & iconPath, ActionType action = ActionType::NoAction);

    static QToolButton * createToolButton
    (const QString & text, const QString & iconPath, ActionType action = ActionType::NoAction);
};
