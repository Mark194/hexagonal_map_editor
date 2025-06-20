//
// Created by Женя on 11.06.2025.
//

#pragma once


#include <QFrame>
#include <QPushButton>
#include <QWidget>


#include "../../interfaces/idual_color_selector.hpp"


class DualColorWidget : public QWidget, public IDualColorSelector
{
public:
    explicit DualColorWidget(QWidget * parent = nullptr);

public slots:
    void swapColors();

    void selectPrimaryColor();

    void selectSecondaryColor();

    void setPrimaryColor(const QColor & color) override;

    [[nodiscard]] QColor primaryColor() const override;

    void setSecondaryColor(const QColor & color);

    [[nodiscard]] QColor secondaryColor() const;

protected:
    bool eventFilter(QObject * obj, QEvent * event) override;

private:
    QFrame * m_primaryColorFrame{};
    QFrame * m_secondaryColorFrame{};

    QColor m_primaryColor;
    QColor m_secondaryColor;

    QPushButton * m_swapButton{};

    void setupUi();

    void updateColors() const;

    void selectColor(QColor & color, const QString & title);
};
