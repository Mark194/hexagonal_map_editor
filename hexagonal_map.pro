QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

SOURCES += \
    entity/builder/gui_builder.cpp \
    entity/controls/mover.cpp \
    entity/controls/zoomer.cpp \
    entity/widgets/hexgrid.cpp \
    entity/widgets/qregular_polygon.cpp \
    form/editor_window.cpp \
    form/subform/grid_sub_form.cpp \
    form/subform/instrument_subform.cpp \
    main.cpp \
    parser/map_parser.cpp \
    parser/map_styles_parser.cpp \
    regulatory.cpp


HEADERS += \
    entity/builder/gui_builder.hpp \
    entity/controls/mover.hpp \
    entity/controls/zoomer.hpp \
    entity/map_style.hpp \
    entity/struct_map.hpp \
    entity/widgets/hexgrid.hpp \
    entity/widgets/qregular_polygon.hpp \
    form/editor_window.hpp \
    form/subform/grid_sub_form.hpp \
    form/subform/instrument_subform.hpp \
    parser/map_parser.hpp \
    parser/map_styles_parser.hpp \
    regulatory.hpp \
    static/project_types.hpp


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
