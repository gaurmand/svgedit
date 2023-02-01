QT += core gui widgets xml
LIBS += -lgtest

HEADERS += $$PWD/view/mainwindow.h \
$$PWD/view/editview.h \
$$PWD/svg/svgparser.h \
$$PWD/svg/svgmodel.h \
$$PWD/svg/svgitem.h \

SOURCES += $$PWD/main.cpp \
$$PWD/view/mainwindow.cpp \
$$PWD/view/editview.cpp \
$$PWD/svg/svgparser.cpp \
$$PWD/svg/svgmodel.cpp \
$$PWD/svg/svgitem.cpp \
