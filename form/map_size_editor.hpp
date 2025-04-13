#pragma once


#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>


class MapSizeEditor : public QDialog
{

    QSpinBox * m_mapWidthEditor;

    QSpinBox * m_mapHeightEditor;

public:

    explicit MapSizeEditor(QWidget * parent = nullptr);

    QSize mapSize() const;

private:

    QLayout * createForm();

    QLayout * createActions();
};

