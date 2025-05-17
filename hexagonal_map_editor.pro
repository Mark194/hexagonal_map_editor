QT       += core gui svg concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

SOURCES += \
    entity/adapter/gui_state_provider.cpp \
    entity/builder/gui_builder.cpp \
    entity/controls/mover.cpp \
    entity/controls/zoomer.cpp \
    entity/widgets/context_panel.cpp \
    entity/widgets/hexgrid.cpp \
    entity/widgets/qregular_polygon.cpp \
    entity/widgets/toolpanel.cpp \
    form/editor_window.cpp \
    form/map_size_editor.cpp \
    form/subform/menu_sub_form.cpp \
    main.cpp \
    parser/map_parser.cpp \
    parser/map_styles_parser.cpp \
    regulatory.cpp \
    saver/map_saver.cpp \
    saver/png_map_saver.cpp \
    services/hex_map_manager.cpp \
    services/loader_styles.cpp \
    saver/svg_map_saver.cpp \
    worker/async_map_worker.cpp


HEADERS += \
    entity/adapter/friend_gui_state_provider.hpp \
    entity/adapter/gui_state_provider.hpp \
    entity/builder/gui_builder.hpp \
    entity/controls/mover.hpp \
    entity/controls/zoomer.hpp \
    entity/map_style.hpp \
    entity/struct_map.hpp \
    entity/widgets/context_panel.hpp \
    entity/widgets/hexgrid.hpp \
    entity/widgets/qregular_polygon.hpp \
    entity/widgets/toolpanel.hpp \
    form/editor_window.hpp \
    form/map_size_editor.hpp \
    form/subform/menu_sub_form.hpp \
    interfaces/imap_saver.hpp \
    interfaces/isubscriber.hpp \
    interfaces/map_saver_base.hpp \
    parser/map_parser.hpp \
    parser/map_styles_parser.hpp \
    regulatory.hpp \
    saver/map_saver.hpp \
    saver/png_map_saver.hpp \
    services/hex_map_manager.hpp \
    services/loader_styles.hpp \
    static/project_types.hpp \
    static/types.hpp \
    saver/svg_map_saver.hpp \
    worker/async_map_worker.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


OBJECTS_DIR += tmp/.o
MOC_DIR     += tmp/.moc
UI_DIR      += tmp/.ui
RCC_DIR     += tmp/.rcc

RESOURCES += \
    resources/resource_icons.qrc
