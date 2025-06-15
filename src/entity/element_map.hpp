#pragma once


#include <qmetatype.h>


#include <QString>


struct ElementMap
{
    QString customColor;

    QString style;

    ElementMap() = default;
};

Q_DECLARE_METATYPE( ElementMap )
