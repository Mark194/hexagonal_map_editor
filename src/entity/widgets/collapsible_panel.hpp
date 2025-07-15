#pragma once


#include "context_panel.hpp"
#include "toolpanel.hpp"


class CollapsiblePanel : public QWidget
{
public:
    CollapsiblePanel(ToolPanel * panel, const QIcon & icon, const QString & text);


    void addWidget(QWidget * widget);

    void clearContent();

private:
    QToolButton * m_controlButton{};

    ContextPanel * m_contextPanel{};
};
