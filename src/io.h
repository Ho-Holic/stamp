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

inline QStringList getDirList(const QString& path)
{
    QStringList result;

    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        result << fileInfo.fileName();
    }

    return result;
}

}
