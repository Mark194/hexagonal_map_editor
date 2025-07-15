#pragma once
#include "../static/project_types.hpp"


class MapBuildingsParser
{
public:
    static BuildingsDict load(const QString & fileName);

    static void save(const QString & fileName, const BuildingsDict & buildings);
};
