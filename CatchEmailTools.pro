QT += core gui widgets network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./curl
DEPENDPATH += ./include ../third_party/headers ./src/common
LIBS += -L./libs
LIBS += -lcurl


SOURCES += \
    main.cpp \
    searchwidget.cpp \
    sonwidget.cpp \
    widget.cpp

HEADERS += \
    searchwidget.h \
    sonwidget.h \
    widget.h

FORMS += \
    searchwidget.ui \
    sonwidget.ui \
    widget.ui

macx {
    ICON = $$PWD/CatchEmailTools.icns
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
