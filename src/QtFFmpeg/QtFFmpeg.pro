NAME         = QtFFmpeg
TARGET       = $${NAME}
QT           = core
QT          -= gui
QT          -= script

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/QtFFmpeg

HEADERS     += $${PWD}/../../include/QtFFmpeg/qtffmpeg.h

SOURCES     += $${PWD}/CPU.cpp
SOURCES     += $${PWD}/Rational.cpp
SOURCES     += $${PWD}/ScaleVector.cpp
SOURCES     += $${PWD}/ScaleFilter.cpp
SOURCES     += $${PWD}/Scaler.cpp
SOURCES     += $${PWD}/Resampler.cpp
SOURCES     += $${PWD}/Process.cpp
SOURCES     += $${PWD}/Codec.cpp
SOURCES     += $${PWD}/Decoder.cpp
SOURCES     += $${PWD}/Encoder.cpp
SOURCES     += $${PWD}/nAudioExtensions.cpp
SOURCES     += $${PWD}/nVideoExtensions.cpp

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

win32 {
LIBS        += -lavcodec
LIBS        += -lavdevice
LIBS        += -lavfilter
LIBS        += -lavformat
LIBS        += -lavutil
LIBS        += -lpostproc
LIBS        += -lswresample
LIBS        += -lswscale
}
