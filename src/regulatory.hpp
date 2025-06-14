#pragma once


#include "entity/command_manager.hpp"
#include "entity/widgets/qregular_polygon.hpp"

#include "form/editor_window.hpp"

#include "worker/async_map_worker.hpp"

#include "interfaces/isubscriber.hpp"
#include "static/project_types.hpp"


class Regulatory : public ISubscriber
{
    EditorWindow * m_editor;

    AsyncMapWorker * m_worker;

    StylesDict m_styles;

    CommandManager * m_commandManager;

public:
    Regulatory();

    ~Regulatory() override;

    void run();

    // ISubscriber interface

    void notifyCreateMap() override;

    void notifyOpenMap() override;

    void notifySaveMap() override;

    void notifyQuit() override;

    void notifyLoadStyles() override;

    void notifyHandleClick() override;

private:
    void loadStyles(const QString & filename);
};
