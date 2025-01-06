#pragma once



#include <QMainWindow>


#include <entity/widgets/hexgrid.hpp>

#include <form/subform/instrument_subform.hpp>
#include "form/subform/grid_sub_form.hpp"


class EditorWindow : public QMainWindow
{
    Q_OBJECT


    HexGrid           * m_hexView;

    InstrumentSubForm * m_instruments;

    GridSubForm       * m_gridSetup;

public:

    EditorWindow(QWidget *parent = nullptr);

    ~EditorWindow();

private:

    void createForm();
};
