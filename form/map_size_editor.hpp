#pragma once


#include <QDialog>
#include <QSpinBox>


class MapSizeEditor : public QDialog
{

    QSpinBox * m_mapWidthEditor;

    QSpinBox * m_mapHeightEditor;

public:

    explicit MapSizeEditor(QWidget * parent = nullptr);

    int mapWidth() const;

    int mapHeight() const;

private:

    void createForm();

    void createActions();
};

