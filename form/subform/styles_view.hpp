#pragma once


#include <QWidget>


#include <entity/widgets/hexgrid.hpp>


class StylesView : public QWidget
{
    Q_OBJECT

    HexGrid * m_hexagonalView;

public:

    explicit StylesView(QWidget *parent = nullptr);

signals:


private:

    void createForm();
};

