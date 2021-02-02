#include "state/OperationBindingSingletone.h"
#include "state/VariableBindingSingletone.h"
#include <QCoreApplication>
#include <QDate>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QTextStream>

QString getProjectPath()
{
    QDir returnMeAfterDir = QDir::current();

    QDir currentDir = QDir::current();

    while (currentDir != QDir::rootPath()) {
        if (currentDir.exists(".stamp")) {

            auto foundProjectPath = currentDir.path();
            currentDir.cd(returnMeAfterDir.path());
            return foundProjectPath;
        } else {
            currentDir.cdUp();
        }
    }

    currentDir.cd(returnMeAfterDir.path());

    return ":"; // fromc qrc file
}

int main(int argc, char* argv[])
{

    QCoreApplication app(argc, argv);

    if (argc < 2) {
        QTextStream out(stdout);
        out << QString("Usage: stamp operation [args...]") << Qt::endl;
        return 0;
    }

    {
        QDir currentDir = QDir::current();
        QString currentDirName = currentDir.dirName();
        QString date = QDate::currentDate().toString();
        QString time = QTime::currentTime().toString();
        QString projectPath = getProjectPath();
        QString templatePath = projectPath + "/.stamp/templates/";

        stamp::VariableBindingSingletone& variables = stamp::variableBindings();
        variables.set("%{currentDirectory}", currentDirName);
        variables.set("%{date}", date);
        variables.set("%{time}", time);
        variables.set("%{project}", projectPath);
        variables.set("%{templates}", templatePath);
    }

    enum { OperationIndex = 1 };

    QStringList arguments = app.arguments();
    QString operationName = arguments.at(OperationIndex);

    arguments.pop_front(); // remove app name
    arguments.pop_front(); // remove operation name

    stamp::Operation* operation = stamp::operationBinding().operation(operationName);
    operation->tryExecute(arguments);

    return 0;
}
