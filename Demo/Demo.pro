#####################################################################
# Automatically generated by qtpromaker
#####################################################################

TEMPLATE = app
TARGET = Demo

SOURCES *= \
    ./main.cpp

HEADERS *= \
    ./include/pa_asio.h \
    ./include/pa_jack.h \
    ./include/pa_linux_alsa.h \
    ./include/pa_mac_core.h \
    ./include/pa_win_ds.h \
    ./include/pa_win_wasapi.h \
    ./include/pa_win_waveformat.h \
    ./include/pa_win_wdmks.h \
    ./include/pa_win_wmme.h \
    ./include/portaudio.h

PATHS *= \
    . \
    ./include

DEPENDPATH *= $$PATHS

INCLUDEPATH *= $$PATHS

LIBS += -L$$PWD/./ -lportaudio

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.