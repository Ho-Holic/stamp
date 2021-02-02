#include "EnvOperation.h"
#include "state/VariableBindingSingletone.h"
#include <QTextStream>

stamp::EnvOperation::EnvOperation()
{
    //
}

void stamp::EnvOperation::execute(const QStringList&)
{
    QTextStream out(stdout);

    for (const auto& pair : stamp::variableBindings().variables().toStdMap()) {
        out << QString("    %1 = %2").arg(pair.first).arg(pair.second) << Qt::endl;
    }
}

QStringList::size_type stamp::EnvOperation::minimumArgumentCount() const
{
    return 0;
}

QString stamp::EnvOperation::usageString() const
{
    return "env";
}
