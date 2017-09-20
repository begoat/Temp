cmake_minimum_required(VERSION 2.8.12)

project(GameHall LANGUAGES CXX)

option(DEVELOP_MODE "enable develop mode" OFF)
set(WATCH_DIR_PATH "\"${PROJECT_SOURCE_DIR}/script/qml\"")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message("The source Dir of this project is :${WATCH_DIR_PATH}")

configure_file (
        "${PROJECT_SOURCE_DIR}/src/utils.h.in"
        "${PROJECT_BINARY_DIR}/utils.h"
)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

set(executable_file ${executable_file}
    "src/main.cpp"
    "src/watchreload/watchreload.h" "src/watchreload/watchreload.cpp"
    "src/logview/logger.h" "src/logview/logger.cpp"
    "src/logview/logview.h" "src/logview/logview.cpp"
    "src/logview/keydock.h" "src/logview/keydock.cpp"
    "src/logview/mainwidget.h" "src/logview/mainwidget.cpp"
    "src/logview/qmllive_global.h"
    "script/qml/qml.qrc"
)
# "src/logview/logview.h" "src/logview/logview.cpp 搞懂为啥不要他
if(DEVELOP_MODE)
    add_executable(${PROJECT_NAME} ${executable_file})
else()
    add_executable(${PROJECT_NAME} "src/main.cpp" "script/qml/qml.qrc")
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Widgets)
