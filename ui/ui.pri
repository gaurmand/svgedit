QT += core gui widgets xml
LIBS += -lgtest

HEADERS += $$PWD/view/mainwindow.h \
$$PWD/view/editview.h \
$$PWD/svg/svgparser.h \

SOURCES += $$PWD/main.cpp \
$$PWD/view/mainwindow.cpp \
$$PWD/view/editview.cpp \
$$PWD/svg/svgparser.cpp \
