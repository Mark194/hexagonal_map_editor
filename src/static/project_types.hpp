#pragma once


#include <QMap>


#include "../entity/building_style.hpp"
#include "../entity/element_map.hpp"
#include "../entity/map_style.hpp"


using MapDict = QMap<QString, ElementMap>;

using StylesDict = QMap<QString, MapStyle>;

using BuildingsDict = QMap<QString, BuildingStyle>;
