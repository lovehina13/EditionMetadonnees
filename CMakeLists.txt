cmake_minimum_required(VERSION 2.6)

project(EditionMetadonnees)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS interfaces)

find_package(Qt4 4.8.7 REQUIRED QtCore QtGui)

qt4_wrap_cpp(MOC_FILES
    include/DocumentationWindow.h
    include/MainWindow.h
    include/QTableWidgetImproved.h)

add_executable(EditionMetadonnees
    source/Data.cpp
    source/DocumentationWindow.cpp
    source/EditionMetadonnees.cpp
    source/MainWindow.cpp
    source/MP3File.cpp
    source/QTableWidgetImproved.cpp
    source/Settings.cpp
    source/Tools.cpp
    interfaces/DocumentationWindow.ui
    interfaces/MainWindow.ui
    resources/Ressources.qrc
    ${MOC_FILES})

target_link_libraries(EditionMetadonnees PUBLIC Qt4::QtCore Qt4::QtGui)

target_include_directories(EditionMetadonnees PUBLIC include)

install(TARGETS EditionMetadonnees DESTINATION bin)
