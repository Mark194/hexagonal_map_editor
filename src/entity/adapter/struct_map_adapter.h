//
// Created by Женя on 19.05.2025.
//

#pragma once
#include <QSize>
#include <QString>


class StructMapAdapter
{
public:

    static QString findMaxElement(const QStringList& elements);

    static QSize maxSize(const QString& elements);
};
