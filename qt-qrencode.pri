QT += quick

unix {
    android {
        INCLUDEPATH += $$PWD/../ext/android_$$ANDROID_TARGET_ARCH/include
        LIBS += -L$$PWD/../ext/android_$$ANDROID_TARGET_ARCH/lib -lqrencode
    } else {
        INCLUDEPATH += $$PWD/../ext/gnu-linux-amd64/include
        LIBS += -L$$PWD/../ext/gnu-linux-amd64/lib -lqrencode
    }
}

HEADERS += \
    $$PWD/qrencodeplugin.h \
    $$PWD/qrcodeitem.h

SOURCES += \
    $$PWD/qrencodeplugin.cpp \
    $$PWD/qrcodeitem.cpp
