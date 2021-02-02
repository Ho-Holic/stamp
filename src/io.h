#pragma once

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QTextStream>

namespace io {

enum FileProcessingMode { Regular,
    WithoutEmptyLines };

inline QStringList getFileAsStringList(const QString& fileName, FileProcessingMode mode = Regular)
{
    QFile file(fileName);
    bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);

    QStringList result;
    if (isOpen) {

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (mode == WithoutEmptyLines && line.trimmed().isEmpty()) {
                continue; // skip empty lines
            }
            result << line;
        }
    }

    return result;
}

inline QString getFileAsString(const QString& fileName)
{
    QFile file(fileName);
    bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (isOpen) {
        QTextStream in(&file);
        return in.readAll(); // rvo
    }
    return QString();
}

enum FileSavingMode { Normal,
    EnsurePath };

inline void saveStringAsFile(const QString& data,
    const QString& filePath,
    FileSavingMode mode = Normal)
{

    if (mode == EnsurePath) {

        QFileInfo info(filePath);
        QDir().mkpath(info.path());
    }

    QFile file(filePath);
    bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (isOpen) {
        QTextStream out(&file);
        out << data;
    }
}

inline QStringList splitStringToList(const QString& string)
{
    QStringList result;
    QString copy = string;

    QTextStream in(&copy);
    while (!in.atEnd()) {
        result << in.readLine();
    }
    return result;
}

inline int findCommentPosition(const QString& commentSymbol, const QString& line)
{

    const QChar QUOTE = '"';

    enum State { Search,
        Skip };
    State state = Search;

    for (int i = 0; i < line.size(); ++i) {
        const QChar c = line.at(i);

        switch (state) {

        case Search:
            if (c == QUOTE) {
                state = Skip;
                break;
            }
            if (line.mid(i, commentSymbol.size()) == commentSymbol) {
                return i;
            }
            break;

        case Skip:
            if (c == QUOTE) {
                state = Search;
            }
            break;
        }
    }
    return line.length();
}
}
