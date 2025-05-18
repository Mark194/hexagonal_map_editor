#pragma once


#include "../interfaces/imap_saver.hpp"


template<typename Derived>
class MapSaverBase : public IMapSaver
{
public:
    static void analyzeScene(const QGraphicsScene * scene)
    {
        if ( scene->items().isEmpty() )

            throw std::logic_error( "Сцена пуста!" );
    }

    static QString saverFormat()
    {
        return Derived::format();
    }
};
