//
// Created by Женя on 14.06.2025.
//

#pragma once


#include <QWidget>


class StyleWidget;

class StyleWidgetGroup final : public QWidget
{
    Q_OBJECT //

public:
    explicit StyleWidgetGroup(QWidget * parent = nullptr);

    void addWidget(StyleWidget * styleWidget);

    void setSelectedWidget(StyleWidget * styleWidget);

    [[nodiscard]] StyleWidget * selectedWidget() const;

    [[nodiscard]] QList<StyleWidget *> styleWidgets() const { return m_styleWidgets; }

private:
    QList<StyleWidget *> m_styleWidgets;

    StyleWidget * m_selectedWidget{};

private slots:
    void changeSelectedWidget();
};
