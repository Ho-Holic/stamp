
// qt
#include <QString>
#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QDate>
#include <QTextStream>
#include "operations/OperationBindingSingletone.h"
#include "operations/VariableBindingSingletone.h"

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

int main(int argc, char* argv[]) {

  QCoreApplication app(argc, argv);

  {
    QDir currentDir = QDir::current();
    QString currentDirName = currentDir.dirName();
    QString date = QDate::currentDate().toString();
    QString time = QTime::currentTime().toString();
    QString projectPath = getProjectPath();
    QString templatePath = projectPath + "/.stamp/templates/";

    stamp::VariableBindingSingletone& variables = stamp::VariableBindingSingletone::getInstance();
    variables.set("%{currentDirectory}",     currentDirName);
    variables.set("%{date}",                 date);
    variables.set("%{time}",                 time);
    variables.set("%{project}",  projectPath);
    variables.set("%{templates}",  templatePath);
  }

  stamp::OperationBindingSingletone& binding = stamp::OperationBindingSingletone::getInstance();

  if (argc < 2) {
    // TODO : show all variants of help
    QTextStream out(stdout);
    out << QString("Usage: stamp operation [args...]") << Qt::endl
        << QString("Example: stamp create class MyClassName") << Qt::endl;
    return 0;
  }

  enum { OperationIndex = 1 };

  QStringList arguments = app.arguments();
  QString operationName = arguments.at(OperationIndex);

  arguments.pop_front(); // remove app name
  arguments.pop_front(); // remove operation name

  stamp::Operation* operation = binding.operation(operationName);
  operation->tryExecute(arguments);

  return 0;
}
