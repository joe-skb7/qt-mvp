QT *= core gui

# Codecs
CODECFORSRC = UTF-8
CODECFORTR = UTF-8

SOURCES += \
    main.cpp \
    wiringform.cpp \
    wiringmodel.cpp \
    wiringpresenter.cpp

HEADERS += \
    wiringform.h \
    wiringmodel.h \
    iwiringview.h \
    wiringpresenter.h

FORMS += \
    wiringform.ui
