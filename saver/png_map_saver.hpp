#pragma once


#include "interfaces/map_saver_base.hpp"


class PngMapSaver : public MapSaverBase<PngMapSaver>
{
public:
    PngMapSaver();

    // IMapSaver interface

    void save(const QString & fileName, QGraphicsScene * scene);

    static QString format();
};

