#include "SystemOperation.h"
#include <QProcess>
#include <QTextStream>
#include <limits>

stamp::SystemOperation::SystemOperation()
    : Operation()
{
    //
}

void stamp::SystemOperation::execute(const QStringList& arguments)
{

    int returnCode = QProcess::execute(arguments.join(' '));
    if (returnCode != 0) {
        QTextStream out(stdout);
        out << QString("Program exits with return code ") << returnCode << Qt::endl;
    }
}

QStringList::size_type stamp::SystemOperation::minimumArgumentCount() const
{
    return ArgumentSize;
}

QString stamp::SystemOperation::usageString() const
{
    return "system [svn add ./]";
}
