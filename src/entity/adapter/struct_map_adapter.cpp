#include "struct_map_adapter.h"


#include <QStringList>


QPair<int, int> parsePair(const QString &s) {
    const int commaPos = s.indexOf(',');
    if (commaPos == -1) return {0, 0};

    bool ok1, ok2;
    const int a = s.left(commaPos).trimmed().toInt(&ok1);
    const int b = s.mid(commaPos + 1).trimmed().toInt(&ok2);

    if (!ok1 || !ok2) return {0, 0};
    return {a, b};
}

QString StructMapAdapter::findMaxElement(const QStringList & elements) {
    if (elements.isEmpty()) return {};

    QString maxStr = elements[0];
    QPair<int, int> maxVal = parsePair(maxStr);

    for (const QString &s : elements)
    {
        if (s > maxStr)
        {
            const auto currentVal = parsePair(s);
            if (currentVal.first > maxVal.first or
                (currentVal.first == maxVal.first and currentVal.second > maxVal.second))
            {
                maxStr = s;
                maxVal = currentVal;
            }
        }
    }

    return maxStr;
}

QSize StructMapAdapter::maxSize(const QString &element)
{
    if (element.isEmpty()) return {0, 0};

    auto maxVal = parsePair(element);

    return {maxVal.first, maxVal.second};
}
