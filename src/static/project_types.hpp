#pragma once


#include <QMap>


#include "../entity/map_style.hpp"
#include "../entity/struct_map.hpp"


using MapDict    = QMap<QString, StructMap>;

using StylesDict = QMap<QString, MapStyle>;
