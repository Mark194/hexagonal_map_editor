#pragma once


#include "static/project_types.hpp"


class MapParser
{
public:
    MapParser();

    MapDict load( QString fileName );
};
