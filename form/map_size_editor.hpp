#pragma once


#include <QCheckBox>
#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>


class MapSizeEditor : public QDialog
{

    QSpinBox  * m_mapWidthEditor;

    QSpinBox  * m_mapHeightEditor;

    QCheckBox * m_rotateEditor;

public:

    explicit MapSizeEditor(QWidget * parent = nullptr);

    QSize mapSize() const;

    bool isRotate() const;

private:

    QLayout * createForm();

    QLayout * createActions();
};

