#include "map_saver.hpp"


#include "svg_map_saver.hpp"
#include "png_map_saver.hpp"


MapSaver::MapSaver() {}

QScopedPointer<IMapSaver> MapSaver::saver(QString format)
{
    if ( format == SvgMapSaver::format() )

        return QScopedPointer<IMapSaver>( new SvgMapSaver() );

    if ( format == PngMapSaver::format() )

        return QScopedPointer<IMapSaver>( new PngMapSaver() );


    throw std::logic_error("Unsupported format!");
}

QString MapSaver::supportedFormats()
{
    return SvgMapSaver::saverFormat() + ";;" + PngMapSaver::saverFormat();
}
