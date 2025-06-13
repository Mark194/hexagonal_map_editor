#pragma once


#include "../../form/editor_window.hpp"

#include "../../static/action_types.hpp"
#include "../../static/project_types.hpp"
#include "../../static/types.hpp"


class GuiStateProvider : public QObject
{
    Q_OBJECT public:
    GuiStateProvider();

    ~GuiStateProvider() override;

    static void createRelations(EditorWindow * window);

    static void loadCells(QGraphicsScene * graphicsScene, const HexGridCells & cells);

    static void clearCells(EditorWindow * window);

    static void loadCoords(const HexGridCells & cells, const QStringList & coords);

    static QGraphicsScene * scene(const EditorWindow * window);

    static void loadStylesMiniatures(const EditorWindow * window, const StylesDict & styles);

    static void loadStyles(const HexGridCells & cells, const MapDict & config, const StylesDict & styles);


    static ActionType actionType(const EditorWindow * window);

    static QColor primaryColor(const EditorWindow * window);

    static QWidget * hexView(const EditorWindow * window);
};

