#include "png_map_saver.hpp"


#include <QPainter>


PngMapSaver::PngMapSaver() {}

void PngMapSaver::save(const QString & fileName, QGraphicsScene * scene)
{
    MapSaverBase<PngMapSaver>::analyzeScene( scene );


    scene->clearSelection();

    scene->setSceneRect( scene->itemsBoundingRect() );

    QImage img( scene->sceneRect().size().toSize(), QImage::Format_ARGB32 );

    img.fill( Qt::transparent );

    QPainter painter( &img );

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    scene->render( &painter );

    img.save( fileName );
}

QString PngMapSaver::format()
{
    return "PNG (*.png)";
}
