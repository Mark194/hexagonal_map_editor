//
// Created by Женя on 11.06.2025.
//

#pragma once


#include <QFrame>
#include <QPushButton>
#include <QWidget>


class DualColorWidget : public QWidget
{
public:
    explicit DualColorWidget(QWidget * parent = nullptr);

public slots:
    void swapColors();

    void selectPrimaryColor();

    void selectSecondaryColor();

    [[nodiscard]] QColor primaryColor() const;

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
