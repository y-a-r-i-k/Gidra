#==============================================#
#                   Gidra                      #
# Gidra is fast and simple password manager    #
# Under the MIT license.                       #
#==============================================#


QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hiddeninterface.cpp \
    infodialog.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp

HEADERS += \
    QStringEncryptionXOR.h \
    hiddeninterface.h \
    infodialog.h \
    loginform.h \
    mainwindow.h \
    settingsdialog.h

FORMS += \
    hiddeninterface.ui \
    infodialog.ui \
    loginform.ui \
    mainwindow.ui \
    settingsdialog.ui

TRANSLATIONS += \
    gidra_ru_RU.ts \
    gidra_en_US.ts



CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32 {
    RC_ICONS = gidra.ico
}

linux | macx {
    ICON += gidra.ico
}

DISTFILES +=
