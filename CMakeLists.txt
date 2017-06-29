cmake_minimum_required(VERSION 3.3)
project(PlateRecognition)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
include_directories(include)
link_directories(lib)
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

aux_source_directory(src/tools SOURCE_DIR)
aux_source_directory(src/dialogs SOURCE_DIR)
aux_source_directory(src/ui SOURCE_DIR)
aux_source_directory(src/widgets SOURCE_DIR)
aux_source_directory(src/model SOURCE_DIR)

add_executable(${PROJECT_NAME} ${SOURCE_DIR} src/main.cpp)
target_link_libraries(${PROJECT_NAME} libeasypr.a libqiniu.dylib)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Widgets Qt5::Core thirdparty)