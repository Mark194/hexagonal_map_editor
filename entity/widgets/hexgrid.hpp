#pragma once


#include <QGraphicsView>


class HexGrid : public QGraphicsView
{
    QGraphicsScene * m_scene;

public:

    HexGrid(QRectF rect = QRectF(), QWidget * parent = nullptr );
};
