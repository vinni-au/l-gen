#-------------------------------------------------
#
# Project created by QtCreator 2012-02-06T22:00:29
#
#-------------------------------------------------

QT       += core gui xml

TARGET = lgen2
TEMPLATE = app

DEFINES += DIAGNOSTIC          # диагностические сообщения

CONFIG(debug) {
    DEFINES += DEBUG           # отладка
    DEFINES += DEBUG_CTOR      # отладка конструкторов
    DEFINES += DEBUG_DTOR      # отладка деструкторов
    DEFINES += DEBUG_SLOT      # отладка слотов
    DEFINES += DEBUG_SIGNAL    # отладка сигналов
    DEFINES += DEBUG_EVENT     # отладка событий
} else {
}

INCLUDEPATH += .


SOURCES += main.cpp\
        mainwindow.cpp \
    LGen2UI/ontologywidget.cpp \
    LGen2Core/lgen2project.cpp \
    LGen2Core/lkb.cpp \
    LGen2Core/lontologymanager.cpp \
    LGen2Core/lnode.cpp \
    LGen2Core/ledge.cpp \
    LGen2Core/linference.cpp \
    LGen2UI/newprojectdialog.cpp \
    LGen2Core/lontology.cpp \
    LGen2MVC/lontologymodel.cpp \
    LGen2MVC/lontologymodeltreenode.cpp \
    LGen2UI/resultwidget.cpp \
    LGen2Editor/lgen2diagrameditor.cpp \
    LGen2Editor/lgen2objectpropertieseditor.cpp \
    LGen2UI/lgen2editor.cpp \
    LGen2Editor/diagramscene.cpp \
    LGen2Editor/diagramitem.cpp \
    LGen2Editor/arrow.cpp \
    3rdparty/QSugar/QSugar.cpp \
    LGen2MVC/lgen2projectmodel.cpp \
    LGen2MVC/lgen2projectmodeltreenode.cpp \
    LGen2UI/categorizer.cpp

HEADERS  += mainwindow.hpp \
    LGen2UI/ontologywidget.hpp \
    LGen2Core/lgen2project.hpp \
    LGen2Core/lkb.hpp \
    LGen2Core/lontologymanager.hpp \
    LGen2Core/lnode.hpp \
    LGen2Core/ledge.hpp \
    LGen2Core/linference.hpp \
    LGen2UI/newprojectdialog.hpp \
    LGen2Core/lontology.hpp \
    LGen2MVC/lontologymodel.hpp \
    LGen2MVC/lontologymodeltreenode.hpp \
    LGen2UI/resultwidget.hpp \
    LGen2Editor/lgen2diagrameditor.hpp \
    LGen2Editor/lgen2objectpropertieseditor.hpp \
    LGen2UI/lgen2editor.hpp \
    LGen2Editor/diagramscene.hpp \
    LGen2Editor/diagramitem.hpp \
    LGen2Editor/arrow.hpp \
    3rdparty/QSugar/QSugar.hpp \
    global.h \
    LGen2MVC/lgen2projectmodel.hpp \
    LGen2MVC/lgen2projectmodeltreenode.hpp \
    LGen2UI/categorizer.hpp

FORMS    += mainwindow.ui \
    LGen2UI/lgen2editor.ui \
    LGen2UI/ontologywidget.ui \
    LGen2UI/newprojectdialog.ui \
    LGen2UI/resultwidget.ui

RESOURCES += \
    res.qrc
