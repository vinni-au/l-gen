TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    morph_compiler_russian.cpp \
    ../libMAFSA-0.2/automaton_basic.c \
    ../libturglem-0.2/txml.cpp \
    ../libturglem-0.2/prediction.c \
    ../libturglem-0.2/paradigms.c \
    ../libturglem-0.2/lemmatizer.c \
    ../expat-2.1.0/xmltok_ns.c \
    ../expat-2.1.0/xmltok_impl.c \
    ../expat-2.1.0/xmltok.c \
    ../expat-2.1.0/xmlrole.c \
    ../expat-2.1.0/xmlparse.c \
    charset_adapters.c

INCLUDEPATH += \
    ./include/ \
    ./../libMAFSA-0.2/include/ \
    ./../libturglem-0.2/include/ \
    ./../expat-2.1.0/

HEADERS += \
    include/turglem/russian/gram_const.h \
    include/turglem/russian/charset_adapters.hpp \
    include/turglem/russian/charset_adapters.h \
    ../libMAFSA-0.2/include/MAFSA/pool.tcc \
    ../libMAFSA-0.2/include/MAFSA/daciuk.tcc \
    ../libMAFSA-0.2/include/MAFSA/daciuk.hpp \
    ../libturglem-0.2/include/turglem/lemmatizer.tcc \
    ../libturglem-0.2/include/turglem/morph_compiler.t \
    ../libturglem-0.2/include/turglem/morph_compiler.hpp \
    ../libMAFSA-0.2/include/MAFSA/stack.hpp \
    ../libMAFSA-0.2/include/MAFSA/pool.hpp \
    ../libMAFSA-0.2/include/MAFSA/mafsa_internal.h \
    ../libMAFSA-0.2/include/MAFSA/charset_adapter.h \
    ../libMAFSA-0.2/include/MAFSA/automaton_int_pair.h \
    ../libMAFSA-0.2/include/MAFSA/automaton_int.h \
    ../libMAFSA-0.2/include/MAFSA/automaton.h \
    ../libturglem-0.2/include/turglem/prediction.h \
    ../libturglem-0.2/include/turglem/paradigms.h \
    ../libturglem-0.2/include/turglem/lemmatizer.hpp \
    ../libturglem-0.2/include/turglem/lemmatizer.h \
    ../libturglem-0.2/include/txml/txml.hpp \
    ../expat-2.1.0/xmltok_impl.h \
    ../expat-2.1.0/xmltok.h \
    ../expat-2.1.0/xmlrole.h \
    ../expat-2.1.0/winconfig.h \
    ../expat-2.1.0/watcomconfig.h \
    ../expat-2.1.0/utf8tab.h \
    ../expat-2.1.0/nametab.h \
    ../expat-2.1.0/macconfig.h \
    ../expat-2.1.0/latin1tab.h \
    ../expat-2.1.0/internal.h \
    ../expat-2.1.0/iasciitab.h \
    ../expat-2.1.0/expat_external.h \
    ../expat-2.1.0/expat.h \
    ../expat-2.1.0/asciitab.h \
    ../expat-2.1.0/ascii.h \
    ../expat-2.1.0/amigaconfig.h

