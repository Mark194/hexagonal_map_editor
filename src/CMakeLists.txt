cmake_minimum_required(VERSION 3.16)
project(hexagonal_map_editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 5.15.2 REQUIRED COMPONENTS Core Gui Svg Widgets Concurrent)

# Список исходных файлов
set(SOURCES
        entity/adapter/gui_state_provider.cpp
        entity/builder/gui_builder.cpp
        entity/controls/mover.cpp
        entity/controls/zoomer.cpp
        entity/widgets/context_panel.cpp
        entity/widgets/hexgrid.cpp
        entity/widgets/qregular_polygon.cpp
        entity/widgets/toolpanel.cpp
        form/editor_window.cpp
        form/map_size_editor.cpp
        form/subform/menu_sub_form.cpp
        main.cpp
        parser/map_parser.cpp
        parser/map_styles_parser.cpp
        regulatory.cpp
        saver/map_saver.cpp
        saver/png_map_saver.cpp
        services/hex_map_manager.cpp
        services/loader_styles.cpp
        saver/svg_map_saver.cpp
        worker/async_map_worker.cpp
        entity/adapter/struct_map_adapter.cpp
        entity/adapter/struct_map_adapter.h
        entity/widgets/style_widget.cpp
        entity/widgets/style_widget.hpp
        worker/async_style_loader.cpp
        worker/async_style_loader.hpp
        entity/widgets/dual_color_widget.cpp
        entity/widgets/dual_color_widget.hpp
)

# Список заголовочных файлов
set(HEADERS
        entity/adapter/friend_gui_state_provider.hpp
        entity/adapter/gui_state_provider.hpp
        entity/builder/gui_builder.hpp
        entity/controls/mover.hpp
        entity/controls/zoomer.hpp
        entity/map_style.hpp
        entity/struct_map.hpp
        entity/widgets/context_panel.hpp
        entity/widgets/hexgrid.hpp
        entity/widgets/qregular_polygon.hpp
        entity/widgets/toolpanel.hpp
        form/editor_window.hpp
        form/map_size_editor.hpp
        form/subform/menu_sub_form.hpp
        interfaces/imap_saver.hpp
        interfaces/isubscriber.hpp
        interfaces/map_saver_base.hpp
        parser/map_parser.hpp
        parser/map_styles_parser.hpp
        regulatory.hpp
        saver/map_saver.hpp
        saver/png_map_saver.hpp
        services/hex_map_manager.hpp
        services/loader_styles.hpp
        static/project_types.hpp
        static/types.hpp
        saver/svg_map_saver.hpp
        worker/async_map_worker.hpp
        entity/widgets/style_widget.cpp
        entity/widgets/style_widget.hpp
        worker/async_style_loader.cpp
        worker/async_style_loader.hpp
        entity/widgets/dual_color_widget.cpp
        entity/widgets/dual_color_widget.hpp
)

# Ресурсы
set(RESOURCES
        ../resources/resource_icons.qrc
        entity/adapter/struct_map_adapter.cpp
        entity/adapter/struct_map_adapter.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})

# Подключаем необходимые модули Qt
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Svg
        Qt5::Widgets
        Qt5::Concurrent
)

# Для статической линковки (аналог QMAKE_LFLAGS_RELEASE += -static -static-libgcc)
if (WIN32 AND MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS_RELEASE "-static -static-libgcc -static-libstdc++"
    )
endif ()

# Устанавливаем пути для промежуточных файлов
set_target_properties(${PROJECT_NAME} PROPERTIES
        AUTOMOC_DIR "${CMAKE_BINARY_DIR}/tmp/.moc"
        AUTOUIC_DIR "${CMAKE_BINARY_DIR}/tmp/.ui"
        AUTORCC_DIR "${CMAKE_BINARY_DIR}/tmp/.rcc"
)

# Создаем каталоги для промежуточных файлов
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/.moc)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/.ui)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/.rcc)