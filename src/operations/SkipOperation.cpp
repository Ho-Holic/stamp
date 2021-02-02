#include "SkipOperation.h"
#include <QTextStream>

stamp::SkipOperation::SkipOperation()
    : Operation()
{
    //
}

void stamp::SkipOperation::execute(const QStringList& arguments)
{
    Q_UNUSED(arguments);
    QTextStream out(stdout);
    out << QString("Operation skipped") << Qt::endl;
}

QStringList::size_type stamp::SkipOperation::minimumArgumentCount() const
{
    return 0;
}

QString stamp::SkipOperation::usageString() const
{
    return "skip";
}
