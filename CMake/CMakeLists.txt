cmake_minimum_required(VERSION 3.16)
project(opencv_Qt)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(OpenCV REQUIRED)

set(QT_LOCAL_PATH ./Qt/5.13.0) #这里需要填入自己安装的路径
set(CMAKE_PREFIX_PATH ${QT_LOCAL_PATH}/clang_64/lib/cmake)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5QuickControls2 REQUIRED)


find_package(Qt5 COMPONENTS Svg REQUIRED)

include_directories(${QT_LOCAL_PATH}/clang_64/include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/log4qt/include)
# name of executable file and path of source file
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})


#set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment version" FORCE)
#
#get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
#get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
#find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt HINTS "${_qt_bin_dir}")



add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIwONS} ${${Qt5Quick_DEFINITIONS}})
#qt5_add_resources(QT_RESOURCES assets/main.qrc)

file(GLOB SOURCE_FILES main.cpp src/*.h src/*.cpp src/log/*.h src/log/*.cpp src/UI/*.h src/UI/*.cpp)
add_executable(opencv_Qt ${SOURCE_FILES})

list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/log4qt/liblog4qt.a)

target_link_libraries(opencv_Qt ${OpenCV_LIBS} Qt5::Widgets Qt5::OpenGL Qt5::Core Qt5::Gui Qt5::Qml  Qt5::Quick Qt5::QuickControls2 Qt5::Svg ${libs})


qt5_use_modules(opencv_Qt Core Widgets Gui OpenGL Qml Quick QuickControls2)

