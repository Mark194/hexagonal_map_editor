//
// Created by Женя on 13.06.2025.
//

#pragma once


#include <QGraphicsScene>
#include <QObject>


class SceneClickHandler final : public QObject
{
    Q_OBJECT public:
    explicit SceneClickHandler(QGraphicsScene * scene, QObject * parent = nullptr);

    QGraphicsItem * currentItem() const;

signals:
    void itemClicked();

private:
    QGraphicsScene * m_scene;

    QPointF m_scenePos;

    bool eventFilter(QObject * watched, QEvent * event) override;
};
