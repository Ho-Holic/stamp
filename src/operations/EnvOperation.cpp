#include "EnvOperation.h"
#include <QTextStream>
#include "VariableBindingSingletone.h"

stamp::EnvOperation::EnvOperation()
{
    //
}

void stamp::EnvOperation::execute(const QStringList &)
{
    stamp::VariableBindingSingletone& binding = stamp::VariableBindingSingletone::getInstance();

    QTextStream out(stdout);

    for (const auto& pair : binding.variables().toStdMap()) {
        out << QString("    %1 = %2").arg(pair.first).arg(pair.second) << Qt::endl;
    }
}

QStringList::size_type stamp::EnvOperation::minimumArgumentCount() const
{
    return 0;
}

QString stamp::EnvOperation::usageString() const
{
    return "stamp env";
}
