#pragma once


#include <QGraphicsView>


class HexGrid : public QGraphicsView
{
public:
    HexGrid(const QRectF & rect = QRectF(), QWidget * parent = nullptr);
};
