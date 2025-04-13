#pragma once


#include <QMenuBar>


#include "entity/adapter/friend_gui_state_provider.hpp"


class MenuSubForm : public QMenuBar
{
    DECLARE_GUI_STATE_PROVIDER_FRIEND()

    QAction * m_createMap;

public:
    MenuSubForm();

private:

    void createFileMenu();

    void createStyleMenu();
};

