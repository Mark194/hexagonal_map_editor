#pragma once


#include <QObject>


class ISubscriber : public QObject
{
    Q_OBJECT

public:

    virtual void notifyCreateMap() = 0;
};
