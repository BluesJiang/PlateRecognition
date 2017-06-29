cmake_minimum_required(VERSION 3.3)
project(PlateRecognition)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
#include_directories(${OpenCV_INCLUDES})
find_package(OpenCV REQUIRED)
# Find includes in corresponding build directories

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

# sub directories
add_subdirectory(thirdparty)

set(SOURCE_FILES main.cpp)
aux_source_directory(src SOURCE_DIR)
add_executable(${PROJECT_NAME} ${SOURCE_DIR} src/dialogs/MainWindow.cpp src/dialogs/MainWindow.h src/tools/PlateRecognisor.h src/tools/PlateRecognisor.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/libeasypr.a)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} thirdparty)
# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core)