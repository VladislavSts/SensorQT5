QT += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    Modules \
    Windows/MainWindow \
    Windows/InitWindow \
#    QCustomPlot


SOURCES += \  
    Core/main.cpp \
    Modules/SerialPort.cpp \
    Windows/MainWindow/mainwindow.cpp \
    Windows/InitWindow/InitWindow.cpp \
#    QCustomPlot/qcustomplot.cpp


HEADERS += \   
    Modules/SerialPort.h \
    Windows/MainWindow/mainwindow.h \
    Windows/InitWindow/InitWindow.h \
#    QCustomPlot/qcustomplot.h


FORMS += \
    Windows/MainWindow/mainwindow.ui \
    Windows/InitWindow/InitWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
