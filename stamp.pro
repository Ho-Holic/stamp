VERSION = 1.1.0

TARGET = stamp

CONFIG += qt

QT += core

SOURCES +=  \
    src/main.cpp \
    src/state/OperationBindingSingletone.cpp \
    src/state/VariableBindingSingletone.cpp \
    src/operations/EnvOperation.cpp \
    src/operations/InitProjectOperation.cpp \
    src/operations/Operation.cpp \
    src/operations/CreateProjectOperation.cpp \
    src/operations/SkipOperation.cpp \
    src/operations/ExtractOperation.cpp \
    src/operations/MakedirOperation.cpp \
    src/operations/SystemOperation.cpp \    


HEADERS += \
    src/io.h \
    src/state/OperationBindingSingletone.h \
    src/state/VariableBindingSingletone.h \
    src/operations/EnvOperation.h \
    src/operations/InitProjectOperation.h \
    src/operations/Operation.h \
    src/operations/CreateProjectOperation.h \
    src/operations/SkipOperation.h \
    src/operations/ExtractOperation.h \
    src/operations/MakedirOperation.h \
    src/operations/SystemOperation.h \

INCLUDEPATH += src/

RESOURCES += \
    res/stamp.qrc
