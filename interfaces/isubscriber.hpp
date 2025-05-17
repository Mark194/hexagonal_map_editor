#pragma once


#include <QObject>


class ISubscriber : public QObject
{
    Q_OBJECT

public:

    virtual void notifyCreateMap() = 0;

    virtual void notifySaveMap() = 0;

    virtual void notifyQuit() = 0;
};
