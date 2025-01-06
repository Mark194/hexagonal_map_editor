#pragma once


#include <QWidget>


class InstrumentSubForm : public QWidget
{
    Q_OBJECT

public:

    explicit InstrumentSubForm(QWidget *parent = nullptr);

signals:

private:

    void createForm();

};
