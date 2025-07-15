#pragma once

#include <QString>

struct BuildingStyle
{
    QString color;

    QString imagePath;

    BuildingStyle() = default;

    [[nodiscard]] bool isValid() const
    {
        return not( color.isEmpty() and imagePath.isEmpty() );
    }
};
