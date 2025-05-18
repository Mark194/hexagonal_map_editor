#pragma once


#include "../../form/editor_window.hpp"
#include "../../static/types.hpp"


class GuiStateProvider : public QObject
{
    Q_OBJECT

public:
    GuiStateProvider();

    ~GuiStateProvider() override;

    static void createRelations( EditorWindow * window );

    static void loadCells(EditorWindow * window, const HexGridCells & cells);

    static void clearCells( EditorWindow * window );

    static void loadCoords(const HexGridCells & cells,
                           const QStringList & coords);

    static QGraphicsScene * scene(const EditorWindow * window );
};

