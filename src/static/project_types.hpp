#pragma once


#include <QMap>


#include "../entity/element_map.hpp"
#include "../entity/map_style.hpp"


using MapDict = QMap<QString, ElementMap>;

using StylesDict = QMap<QString, MapStyle>;
