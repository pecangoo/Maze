QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.

SOURCES += \
    eller.cpp \
    gencave.cpp \
    init_cave.cpp \
    main.cpp \
    mainwindow.cpp \
    mikkimouse.cpp \
    parcer.cpp \
    writertofile.cpp

HEADERS += \
    eller.h \
    gencave.h \
    init_cave.h \
    mainwindow.h \
    mikkimouse.h \
    models.h \
    parcer.h \
    writertofile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
