#pragma once


#include <QObject>


class ISubscriber : public QObject
{
    Q_OBJECT //
public:
    ~ISubscriber() override = default;

    virtual void notifyCreateMap() = 0;

    virtual void notifyOpenMap() = 0;

    virtual void notifySaveMap() = 0;

    virtual void notifyQuit() = 0;


    virtual void notifyLoadStyles() = 0;

    virtual void notifyHandleClick() = 0;

    virtual void notifyCreateStyle() = 0;

    virtual void notifyChangeStyle() = 0;

    virtual void notifySaveStyles() = 0;

    virtual void notifyLoadBuildings() = 0;
};
