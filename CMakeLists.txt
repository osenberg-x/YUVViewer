cmake_minimum_required(VERSION 3.5)

project(YUVViewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        main_window.cpp
        main_window.h
        main_window.ui
        viewer.cpp
        viewer.h
        viewer.ui
        utils.cpp
        utils.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(YUVViewer
        ${PROJECT_SOURCES}
    )
else()
    add_executable(YUVViewer
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(YUVViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
