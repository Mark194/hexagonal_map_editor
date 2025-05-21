#pragma once


#include <QString>


struct MapStyle
{
    QString color;

    QString image;

    [[nodiscard]] bool isValid() const
    {
        return not ( color.isEmpty() and image.isEmpty() );
    }
};
