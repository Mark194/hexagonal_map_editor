#pragma once


#include <form/editor_window.hpp>

#include "static/types.hpp"


class GuiStateProvider : public QObject
{
    Q_OBJECT

public:
    GuiStateProvider();

    static void createRelations( EditorWindow * window );

    static void loadCells(EditorWindow * window, const HexGridCells & cells);

    static void clearCells( EditorWindow * window );
};

