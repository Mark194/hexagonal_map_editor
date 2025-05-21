#pragma once


#include <QFutureWatcher>


#include "../static/project_types.hpp"
#include "../static/types.hpp"


using MapDictWatcher = QFutureWatcher<MapDict>;


class AsyncStyleLoader : public QObject
{
    Q_OBJECT public:
    AsyncStyleLoader();

    ~AsyncStyleLoader() override;

    void setStyles(const StylesDict & styles);

    void setCells(const HexGridCells & cells);

    void start(const QString & fileName);

private:
    HexGridCells m_gridCells;
    StylesDict m_stylesDict;

    QFuture<MapDict> m_parseFuture;
    MapDictWatcher m_parseWatcher;

    void loadStyles() const;
};
