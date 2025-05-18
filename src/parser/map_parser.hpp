#pragma once


#include "../static/project_types.hpp"


class MapParser
{
public:
    MapParser();

    static MapDict load( const QString & fileName );
};
