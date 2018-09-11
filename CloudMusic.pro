SOURCES += \
    src/widgets/bottomwidget.cpp \
    src/widgets/mainwidget.cpp \
    src/widgets/sidewidget.cpp \
    src/main.cpp \
    src/music_api/neteaseapi.cpp \
    src/widgets/imagepusubutton.cpp \
    src/widgets/toplistwidget.cpp \
    src/widgets/titlewidget.cpp \
    src/widgets/topplaylistwidget.cpp \
    src/widgets/djradiowidget.cpp \
    src/widgets/albumwidget.cpp \
    src/widgets/playerwidget.cpp \
    src/player/aplyer.cpp \
    src/widgets/musiclistwidget.cpp \
    src/widgets/musicplaylisttable.cpp \
    src/player/playlist.cpp \
    src/widgets/musicnamewidget.cpp

QT              +=      widgets sql network  multimedia  x11extras

HEADERS += \
    src/widgets/bottomwidget.h \
    src/widgets/mainwidget.h \
    src/widgets/sidewidget.h \
    src/music_api/neteaseapi.h \
    src/widgets/imagepusubutton.h \
    src/widgets/toplistwidget.h \
    src/widgets/titlewidget.h \
    src/widgets/topplaylistwidget.h \
    src/widgets/djradiowidget.h \
    src/widgets/albumwidget.h \
    src/widgets/playerwidget.h \
    src/player/aplyer.h \
    src/widgets/musiclistwidget.h \
    src/widgets/musicplaylisttable.h \
    src/player/playlist.h \
    src/widgets/musicnamewidget.h


RESOURCES += \
    icons.qrc

CONFIG      += c++11 link_pkgconfig

PKGCONFIG   += xcb
LIBS        += -lX11 -lXext

RC_ICONS    += /icons/cloud_music_logo.ico
DISTFILES +=
