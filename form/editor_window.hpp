#pragma once


#include <QMainWindow>


#include <entity/adapter/friend_gui_state_provider.hpp>

#include <entity/widgets/hexgrid.hpp>


#include <form/subform/grid_sub_form.hpp>
#include <form/subform/menu_sub_form.hpp>

#include <interfaces/isubscriber.hpp>



class EditorWindow : public QMainWindow
{
    Q_OBJECT

    DECLARE_GUI_STATE_PROVIDER_FRIEND()

    ISubscriber       * m_subscriber;

    HexGrid           * m_hexView;

    GridSubForm       * m_gridSetup;

    MenuSubForm       * m_menuForm;

    QObjectList         m_actions;

public:

    EditorWindow(ISubscriber * subscriber, QWidget *parent = nullptr);

    ~EditorWindow();

private:

    void createForm();

    void createActions();
};
