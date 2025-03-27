#include "loader_styles.hpp"


#include <entity/widgets/qregular_polygon.hpp>


LoaderStyles::LoaderStyles(
    QObject *parent)
    : QObject{parent}
{
}

void LoaderStyles::load(QGraphicsScene * view, StylesDict styles)
{
    // for ( auto style : styles )
    // {
    //     QRegularPolygon * polygon = new QRegularPolygon()
    // }
}
