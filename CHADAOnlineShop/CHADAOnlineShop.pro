TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT

SOURCES += main.cpp \
    account.cpp \
    cart.cpp \
    chadaonlineshopdisplay.cpp \
    datahandler.cpp \
    item.cpp \
    itemdatahandler.cpp \
    iteminfo.cpp \
    itempurchase.cpp \
    screen.cpp \
    selections.cpp \
    selleraccount.cpp \
    sellerdatahandler.cpp \
    sellerscreen.cpp \
    shopscreen.cpp \
    signinscreen.cpp \
    systemmanager.cpp \
    utils.cpp \
    admin.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    account.h \
    cart.h \
    chadaonlineshopdisplay.h \
    datahandler.h \
    dirent.h \
    item.h \
    itemdatahandler.h \
    iteminfo.h \
    itempurchase.h \
    mastercard.h \
    screen.h \
    selections.h \
    selleraccount.h \
    sellerdatahandler.h \
    sellerscreen.h \
    shopscreen.h \
    signinscreen.h \
    systemmanager.h \
    utils.h \
    admin.h


win32: LIBS += -L$$PWD/./ -lmastercard

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
