VERSION = 1.1.0

TARGET = stamp

CONFIG += qt

QT += core

SOURCES +=  \
    src/main.cpp \
    src/operations/EnvOperation.cpp \
    src/operations/InitProjectOperation.cpp \
    src/operations/OperationBindingSingletone.cpp \
    src/operations/Operation.cpp \
    src/operations/CreateProjectOperation.cpp \
    src/operations/SkipOperation.cpp \
    src/operations/VariableBindingSingletone.cpp \
    src/operations/ExtractOperation.cpp \
    src/operations/MakedirOperation.cpp \
    src/operations/SystemOperation.cpp \    


HEADERS += \
    src/io.h \
    src/operations/EnvOperation.h \
    src/operations/InitProjectOperation.h \
    src/operations/OperationBindingSingletone.h \
    src/operations/Operation.h \
    src/operations/CreateProjectOperation.h \
    src/operations/SkipOperation.h \
    src/operations/VariableBindingSingletone.h \
    src/operations/ExtractOperation.h \
    src/operations/MakedirOperation.h \
    src/operations/SystemOperation.h \

INCLUDEPATH += src/

RESOURCES += \
    res/stamp.qrc
