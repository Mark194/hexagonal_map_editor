cmake_minimum_required(VERSION 3.16)

project(hexagonal_map_editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# Настройка путей для промежуточных файлов
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Поиск Qt5
find_package(Qt5 5.15.2 REQUIRED COMPONENTS Core Gui Svg Widgets Concurrent)

# Подключаем поддиректорию с исходниками
add_subdirectory(src)