#pragma once


#include <QMenuBar>


class MenuSubForm : public QMenuBar
{
public:
    MenuSubForm();

private:

    void createFileMenu();

    void createStyleMenu();
};

