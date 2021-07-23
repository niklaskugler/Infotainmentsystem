QT       += core gui
QT += multimedia
QT += 3drender

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11

# Einbindung der externen OpenSSL Bibliothek
win32 |  win64 {
    LIBS += -L$$PWD/thirdParty/openssl/ -llibcrypto-1_1-x64
    LIBS += -L$$PWD/thirdParty/openssl/ -llibssl-1_1-x64
}


include($$PWD/core/core.pri)
include($$PWD/gui/gui.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    infotainmentsystemWindow.cpp \
    main.cpp

HEADERS += \
    infotainmentsystemWindow.h

FORMS += \
    infotainmentsystemWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Car_Model.qrc \
    Images.qrc \
    Music.qrc \
    qml.qrc

DISTFILES += \
    qml/Fahrzeug_Modell-Formular.ui.qml \
    qml/Klima_Display-Formular.ui.qml \
    qml/Switch_button-Formular.ui.qml
