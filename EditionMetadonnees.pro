#===============================================================================
# Name        : EditionMetadonnees.pro
# Author      : Alexis Foerster (alexis.foerster@gmail.com)
# Version     : 1.0.0 (01/02/2019)
# Description : Qt project file of the EditionMetadonnees project
#===============================================================================

TEMPLATE = app
TARGET = EditionMetadonnees
DEPENDPATH += . include source
INCLUDEPATH += . include
OBJECTS_DIR = objects
MOC_DIR = objects
RCC_DIR = objects
UI_DIR = objects

HEADERS += include/Data.h \
           include/DocumentationWindow.h \
           include/MainWindow.h \
           include/MP3File.h \
           include/Settings.h
SOURCES += source/EditionMetadonnees.cpp \
           source/Data.cpp \
           source/DocumentationWindow.cpp \
           source/MainWindow.cpp \
           source/MP3File.cpp \
           source/Settings.cpp
FORMS += interfaces/DocumentationWindow.ui \
         interfaces/MainWindow.ui
RESOURCES += ressources/Ressources.qrc

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
# QMAKE_CXXFLAGS += -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wunused-parameter -Werror
