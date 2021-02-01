#include "InitProjectOperation.h"
#include <QDir>

stamp::InitProjectOperation::InitProjectOperation()
{
    //
}

void stamp::InitProjectOperation::execute(const QStringList& arguments)
{
    const QString& initPath = arguments.at(InitDirPathIndex);
    QDir().mkpath(initPath + "/.stamp/templates/");
}

QStringList::size_type stamp::InitProjectOperation::minimumArgumentCount() const
{
    return Argument::ArgumentSize;
}

QString stamp::InitProjectOperation::usageString() const
{
    return "init ./some/path/";
}
