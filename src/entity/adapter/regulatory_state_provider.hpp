//
// Created by Женя on 20.06.2025.
//

#pragma once

#include <QObject>


#include "../map_style.hpp"


#include "../../interfaces/isubscriber.hpp"

class RegulatoryStateProvider final : public QObject
{
    Q_OBJECT //

public:
    static MapStyle mapStyle(ISubscriber * subscriber, const QString & styleName);
};
