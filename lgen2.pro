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

INCLUDEPATH += . \
    3rdparty/libMAFSA-0.2/include \
    3rdparty/libturglem-0.2/include \
    3rdparty/expat-2.1.0/ \
    3rdparty/turglem-russian-0.2/include


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
    LGen2UI/categorizer.cpp \
    LGen2UI/DataUIDialogs/nodedialog.cpp \
    LGen2UI/DataUIDialogs/situationdialog.cpp \
    LGen2UI/DataUIDialogs/edgedialog.cpp \
    LGen2UI/treebox.cpp \
    3rdparty/libMAFSA-0.2/include/MAFSA/daciuk.cpp \
    3rdparty/libturglem-0.2/include/turglem/morph_compiler.tcc \
    3rdparty/libturglem-0.2/include/turglem/lemmatizer.tcc \
    3rdparty/libturglem-0.2/txml.cpp \
    3rdparty/libturglem-0.2/prediction.c \
    3rdparty/libturglem-0.2/paradigms.c \
    3rdparty/libturglem-0.2/lemmatizer.c \
    3rdparty/expat-2.1.0/xmltok_ns.c \
    3rdparty/expat-2.1.0/xmltok_impl.c \
    3rdparty/expat-2.1.0/xmltok.c \
    3rdparty/expat-2.1.0/xmlrole.c \
    3rdparty/expat-2.1.0/xmlparse.c \
    3rdparty/libturglem-0.2/include/turglem/morph_compiler.cpp \
    3rdparty/libMAFSA-0.2/automaton_basic.c \
    3rdparty/turglem-russian-0.2/charset_adapters.c \
    LGen2UI/lemmatizerform.cpp

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
    LGen2UI/categorizer.hpp \
    LGen2UI/DataUIDialogs/nodedialog.hpp \
    LGen2UI/DataUIDialogs/situationdialog.hpp \
    LGen2UI/DataUIDialogs/edgedialog.hpp \
    LGen2UI/treebox.hpp \
    3rdparty/libMAFSA-0.2/include/MAFSA/stack.hpp \
    3rdparty/libMAFSA-0.2/include/MAFSA/mafsa_internal.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/charset_adapter.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton_int_pair.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton_int.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/stack.hpp \
    3rdparty/libMAFSA-0.2/include/MAFSA/pool.tcc \
    3rdparty/libMAFSA-0.2/include/MAFSA/mafsa_internal.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/daciuk.tcc \
    3rdparty/libMAFSA-0.2/include/MAFSA/charset_adapter.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton_int_pair.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton_int.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/stack.hpp \
    3rdparty/libMAFSA-0.2/include/MAFSA/mafsa_internal.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/charset_adapter.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton_int_pair.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton_int.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/automaton.h \
    3rdparty/libMAFSA-0.2/include/MAFSA/pool.hpp \
    3rdparty/libturglem-0.2/include/turglem/prediction.h \
    3rdparty/libturglem-0.2/include/turglem/paradigms.h \
    3rdparty/libturglem-0.2/include/turglem/lemmatizer.hpp \
    3rdparty/libturglem-0.2/include/turglem/lemmatizer.h \
    3rdparty/libturglem-0.2/include/txml/txml.hpp \
    3rdparty/expat-2.1.0/xmltok_impl.h \
    3rdparty/expat-2.1.0/xmltok.h \
    3rdparty/expat-2.1.0/xmlrole.h \
    3rdparty/expat-2.1.0/winconfig.h \
    3rdparty/expat-2.1.0/watcomconfig.h \
    3rdparty/expat-2.1.0/utf8tab.h \
    3rdparty/expat-2.1.0/nametab.h \
    3rdparty/expat-2.1.0/macconfig.h \
    3rdparty/expat-2.1.0/latin1tab.h \
    3rdparty/expat-2.1.0/internal.h \
    3rdparty/expat-2.1.0/iasciitab.h \
    3rdparty/expat-2.1.0/expat_external.h \
    3rdparty/expat-2.1.0/expat.h \
    3rdparty/expat-2.1.0/asciitab.h \
    3rdparty/expat-2.1.0/ascii.h \
    3rdparty/expat-2.1.0/amigaconfig.h \
    3rdparty/turglem-russian-0.2/include/turglem/russian/gram_const.h \
    3rdparty/turglem-russian-0.2/include/turglem/russian/charset_adapters.hpp \
    3rdparty/turglem-russian-0.2/include/turglem/russian/charset_adapters.h \
    LGen2UI/lemmatizerform.hpp

FORMS    += mainwindow.ui \
    LGen2UI/lgen2editor.ui \
    LGen2UI/ontologywidget.ui \
    LGen2UI/newprojectdialog.ui \
    LGen2UI/resultwidget.ui \
    LGen2UI/DataUIDialogs/nodedialog.ui \
    LGen2UI/DataUIDialogs/situationdialog.ui \
    LGen2UI/DataUIDialogs/edgedialog.ui \
    LGen2UI/lemmatizerform.ui

RESOURCES += \
    res.qrc
