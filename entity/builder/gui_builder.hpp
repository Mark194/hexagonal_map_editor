#pragma once


#include <QPushButton>


class GuiBuilder
{
public:

    GuiBuilder();

    static QPushButton * createButton( QString iconPath );
};
