#pragma once


#include <QGraphicsView>
#include <QObject>


class Mover : public QObject
{
    Q_OBJECT

    QGraphicsView * m_view;

    double m_originX;

    double m_originY;

    Qt::MouseButtons m_pressedButtons;

public:

    explicit Mover(QGraphicsView *view = nullptr);

    // QObject interface

    bool eventFilter(QObject * watched, QEvent * event);
};
