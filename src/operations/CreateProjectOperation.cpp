#include "CreateProjectOperation.h"
#include "io.h"
#include "state/OperationBindingSingletone.h"
#include "state/VariableBindingSingletone.h"
#include <QDate>
#include <QDir>
#include <QTime>

stamp::CreateProjectOperation::CreateProjectOperation()
    : Operation()
{
    //
}

void stamp::CreateProjectOperation::execute(const QStringList& arguments)
{

    stamp::ArgumentPairList namedArguments;
    QStringList nonameArguments;

    stamp::Operation::splitArguments(arguments, namedArguments, nonameArguments);

    // TODO: check that module exists and all files are ok

    QDir currentDir = QDir::current();

    QString destinationFilePath = QDir::toNativeSeparators(nonameArguments.at(TargetPathIndex));
    if (destinationFilePath.endsWith(QDir::separator()))
        destinationFilePath.chop(1);

    QString templateName = nonameArguments.at(TemplateNameIndex);
    QString targetName = destinationFilePath.section(QDir::separator(), -1); // only file name
    QString targetPath = destinationFilePath.section(QDir::separator(), 0, -2); // file path w/o name
    if (targetPath.isEmpty())
        targetPath = currentDir.path(); // current dir

    //
    // TODO: add context id, to remove variables from binding after operations is done
    //
    stamp::VariableBindingSingletone& binding = stamp::variableBindings();
    binding.set("%{templateName}", templateName);
    binding.set("%{targetPath}", targetPath);
    binding.set("%{targetName}", targetName);

    // insert named arguments
    processNamedArguments(namedArguments);

    QString scriptPath = QString("%{templates}/%1/%1.create.operation").arg(templateName);
    binding.replaceVariablesIn(scriptPath);

    QStringList script = io::getFileAsStringList(scriptPath, io::WithoutEmptyLines);
    binding.replaceVariablesIn(script);

    QTextStream out(stdout);
    out << "using template " << scriptPath << Qt::endl;

    stamp::operationBinding().executeScript(script);
}

QStringList::size_type stamp::CreateProjectOperation::minimumArgumentCount() const
{
    return ArgumentSize;
}

QString stamp::CreateProjectOperation::usageString() const
{
    // TODO: show all available create operations by scanning project folder
    return "create [module, ...] MyCustomName";
}

void stamp::CreateProjectOperation::processNamedArguments(const stamp::ArgumentPairList& namedArguments)
{
    Q_UNUSED(namedArguments);
}
