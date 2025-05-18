#pragma once


#include <QGraphicsScene>
#include <QObject>


#include "../static/project_types.hpp"


class LoaderStyles : public QObject
{
    Q_OBJECT

public:

    explicit LoaderStyles(QObject *parent = nullptr);

    void load( QGraphicsScene * view, StylesDict styles );

signals:
};

