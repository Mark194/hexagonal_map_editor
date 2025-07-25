#pragma once


#include "../static/project_types.hpp"


class MapStylesParser
{
public:
    MapStylesParser();

    static StylesDict load(const QString & fileName);

    static void save(const QString & fileName, const StylesDict & stylesDict);
};
