#pragma once


#include <QButtonGroup>
#include <QMainWindow>


#include "../entity/adapter/friend_gui_state_provider.hpp"

#include "../entity/widgets/hexgrid.hpp"
#include "../entity/widgets/context_panel.hpp"
#include "../entity/widgets/dual_color_widget.hpp"


#include "../form/subform/menu_sub_form.hpp"

#include "../interfaces/isubscriber.hpp"


class EditorWindow final : public QMainWindow
{
    Q_OBJECT DECLARE_GUI_STATE_PROVIDER_FRIEND()

    ISubscriber * m_subscriber;

    HexGrid * m_hexView{};

    MenuSubForm * m_menuForm;

    QObjectList m_actions;

    ContextPanel * m_contextPanel;

    QButtonGroup * m_buttonGroup;

    DualColorWidget * m_dualColorWidget;

public:
    explicit EditorWindow(ISubscriber * subscriber, QWidget * parent = nullptr);

    ~EditorWindow() override;

private:
    void createForm();

    void createActions();
};
