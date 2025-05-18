#pragma once


#include "../static/project_types.hpp"


class MapStylesParser
{
public:
    MapStylesParser();

    StylesDict load( QString fileName );
};
