#pragma once


#include "../interfaces/imap_saver.hpp"


class MapSaver
{
public:
    MapSaver();

    static QScopedPointer<IMapSaver> saver(const QString & format);

    static QString supportedFormats();
};

