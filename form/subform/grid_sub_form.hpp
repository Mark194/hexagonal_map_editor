#pragma once


#include <QWidget>


class GridSubForm : public QWidget
{
    Q_OBJECT

public:

    explicit GridSubForm(QWidget *parent = nullptr);

signals:

private:

    void createSubForm();
};
