#pragma once


#include <QString>


struct MapStyle
{
    QString color;

    QString image;

    MapStyle() = default;

    [[nodiscard]] bool isValid() const
    {
        return not( color.isEmpty() and image.isEmpty() );
    }
};

Q_DECLARE_METATYPE( MapStyle )
