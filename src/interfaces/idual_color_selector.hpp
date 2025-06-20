//
// Created by Женя on 20.06.2025.
//

#pragma once


#include <QColor>


class IDualColorSelector
{
public:
    virtual ~IDualColorSelector() = default;

    virtual void setPrimaryColor(const QColor & color) = 0;

    [[nodiscard]] virtual QColor primaryColor() const = 0;
};

Q_DECLARE_METATYPE( IDualColorSelector * )
