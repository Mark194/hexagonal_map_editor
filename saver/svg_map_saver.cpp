#include "svg_map_saver.hpp"


#include <QPainter>
#include <QSvgGenerator>


SvgMapSaver::SvgMapSaver() {}

void SvgMapSaver::save(const QString & fileName, QGraphicsScene * scene)
{
    MapSaverBase<SvgMapSaver>::analyzeScene( scene );

    QSvgGenerator generator;
    generator.setFileName( fileName );
    generator.setSize(QSize(scene->width(), scene->height()));
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height()));
    generator.setTitle( "Hexagonal Map" );
    generator.setDescription( "Created by Hexagonal Map Editor" );

    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();
}

QString SvgMapSaver::format()
{
    return "SVG (*.svg)";
}
