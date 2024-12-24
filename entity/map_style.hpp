#pragma once


#include <QString>


struct MapStyle
{
    QString color;

    QString image;

    bool isValid()
    {
        return not ( color.isEmpty() and image.isEmpty() );
    }
};
