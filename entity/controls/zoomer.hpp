#pragma once


#include <QGraphicsView>
#include <QObject>


class Zoomer : public QObject
{
    Q_OBJECT

    QGraphicsView * m_view;

    Qt::KeyboardModifiers m_modifiers;

    double m_baseZoomFactor;

    QPointF m_targetScenePos;

    QPointF m_targetViewportPos;

public:
    explicit Zoomer(QGraphicsView *view = nullptr);


    void setBaseZoomFactor(double baseZoomFactor);

    void setModifiers(const Qt::KeyboardModifiers & modifiers);


    void gentleZoom(double factor);

signals:

    void zoomed();

private:

    bool eventFilter( QObject * object, QEvent * event );

};
