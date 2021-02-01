// self
#include "MakedirOperation.h"

// qt
#include <QDir>

stamp::MakedirOperation::MakedirOperation()
    : Operation()
{
    //
}

void stamp::MakedirOperation::execute(const QStringList& arguments)
{

    QString pathForCreation = arguments.at(CreateDirPathIndex);

    // QDir() is current directory i.e. "./"
    bool isExist = QDir().mkpath(pathForCreation);
    Q_UNUSED(isExist);
}

QStringList::size_type stamp::MakedirOperation::minimumArgumentCount() const
{
    return ArgumentSize;
}

QString stamp::MakedirOperation::usageString() const
{
    return "Example: makedir some/new/dir";
}
