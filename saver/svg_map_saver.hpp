#pragma once


#include <interfaces/map_saver_base.hpp>


class SvgMapSaver : public MapSaverBase<SvgMapSaver>
{
public:
    SvgMapSaver();

    // IMapSaver interface

    void save(const QString & fileName, QGraphicsScene * scene);

    static QString format();
};

