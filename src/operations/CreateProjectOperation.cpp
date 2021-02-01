// self
#include "CreateProjectOperation.h"
#include "OperationBindingSingletone.h"
#include "VariableBindingSingletone.h"
#include "io.h"

// qt
#include <QDir>
#include <QDate>
#include <QTime>

// tmp
#include <QDebug>

stamp::CreateProjectOperation::CreateProjectOperation()
: Operation() {
  //
}

void stamp::CreateProjectOperation::execute(const QStringList& arguments) {

  stamp::ArgumentPairList namedArguments;
  QStringList nonameArguments;

  stamp::Operation::splitArguments(arguments, namedArguments, nonameArguments);


  // TODO: check that module exists and all files are ok

  QDir currentDir = QDir::current();

  QString destinationFilePath = QDir::toNativeSeparators(nonameArguments.at(ProjectNameIndex));
  if (destinationFilePath.endsWith(QDir::separator())) destinationFilePath.chop(1);

  QString templateType = nonameArguments.at(ModuleTypeIndex);
  QString templateName = destinationFilePath.section(QDir::separator(), -1); // only file name
  QString templatePath = destinationFilePath.section(QDir::separator(), 0, -2); // file path w/o name
  if (templatePath.isEmpty()) templatePath = "."; // current dir

  QString upperCaseTemplatePath = templatePath.toUpper();

  stamp::VariableBindingSingletone& binding = stamp::VariableBindingSingletone::getInstance();
  binding.set("%{templateType}",          templateType);
  binding.set("%{templateName}",          templateName);
  binding.set("%{modulePath}",          templatePath);
  binding.set("%{upperCaseTemplatePath}", upperCaseTemplatePath);

  // insert named arguments
  processNamedArguments(namedArguments);

  QString scriptPath = QString("%{templates}/%1/%1.create.operation").arg(templateType);
  binding.replaceVariablesIn(scriptPath);

  QTextStream out(stdout);
  out << "using template " << scriptPath << Qt::endl;

  QStringList script = io::getFileAsStringList(scriptPath, io::WithoutEmptyLines);
  binding.replaceVariablesIn(script);

  stamp::OperationBindingSingletone::getInstance().executeScript(script);
}

QStringList::size_type stamp::CreateProjectOperation::minimumArgumentCount() const {
  return ArgumentSize;
}

QString stamp::CreateProjectOperation::usageString() const {
  // TODO: show all available create operations
  return "Example: stamp create [module, ...] MyCustomName";
}

void stamp::CreateProjectOperation::processNamedArguments(const stamp::ArgumentPairList& namedArguments) {
  //
    Q_UNUSED(namedArguments);
}
