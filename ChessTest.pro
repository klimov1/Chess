TEMPLATE = app

QT += qml quick
CONFIG += c++14

SOURCES += main.cpp \
    ChessEngine/item.cpp \
    ChessEngine/itemfactory.cpp \
    Utils/serialization.cpp \
    Utils/typeconvertors.cpp \
    ChessEngine/board.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ChessEngine/defines.h \
    ChessEngine/item.h \
    ChessEngine/utils.h \
    ChessEngine/itemfactory.h \
    Utils/serialization.h \
    Utils/typeconvertors.h \
    ChessEngine/board.h

