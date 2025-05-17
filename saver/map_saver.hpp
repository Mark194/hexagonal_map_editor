#pragma once


#include <interfaces/imap_saver.hpp>


class MapSaver
{
public:
    MapSaver();

    static QScopedPointer<IMapSaver> saver(QString format);

    static QString supportedFormats();
};

