#pragma once


#include <QGraphicsScene>


class IMapSaver
{
public:

    virtual ~IMapSaver() = default;

    virtual void save(const QString & fileName, QGraphicsScene * scene) = 0;
};
