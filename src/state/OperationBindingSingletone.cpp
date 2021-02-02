#include "OperationBindingSingletone.h"
#include "operations/CreateProjectOperation.h"
#include "operations/EnvOperation.h"
#include "operations/ExtractOperation.h"
#include "operations/InitProjectOperation.h"
#include "operations/MakedirOperation.h"
#include "operations/SkipOperation.h"
#include "operations/SystemOperation.h"
#include <QTextStream>

namespace {
const QString DEFAULT_OPERATION = "skip";
}

stamp::OperationBindingSingletone& stamp::operationBinding()
{
    static OperationBindingSingletone instance;
    return instance;
}

stamp::Operation* stamp::OperationBindingSingletone::operation(const QString& operationName)
{
    auto it = m_operations.find(operationName);

    Q_ASSERT_X(m_operations.find(DEFAULT_OPERATION) != m_operations.end(), __FUNCTION__,
        "Default operation must be in container");

    return (it != m_operations.end()) ? it->second.get() : m_operations[DEFAULT_OPERATION].get();
}

stamp::OperationBindingSingletone::OperationBindingSingletone()
{
    m_operations = {
        { "create", std::make_shared<stamp::CreateProjectOperation>() },
        { "skip", std::make_shared<stamp::SkipOperation>() },
        { "extract", std::make_shared<stamp::ExtractOperation>() },
        { "makedir", std::make_shared<stamp::MakedirOperation>() },
        { "system", std::make_shared<stamp::SystemOperation>() },
        { "init", std::make_shared<stamp::InitProjectOperation>() },
        { "env", std::make_shared<stamp::EnvOperation>() },
    };
}

void stamp::OperationBindingSingletone::executeScript(const QStringList& script)
{
    // TODO: replace recursion with queue

    QTextStream out(stdout);

    for (QStringList::ConstIterator it = script.begin(); it != script.end(); ++it) {
        const QString& actionLine = (*it);

        out << actionLine << Qt::endl;

        QStringList splittedArguments = stamp::Operation::escapeSplit(actionLine);

        if (!splittedArguments.isEmpty()) {
            QString actionName = splittedArguments.at(ActionIndex);
            splittedArguments.pop_front(); // pop operation name

            stamp::Operation* currentOperation = this->operation(actionName);
            currentOperation->tryExecute(splittedArguments);
        }
    }
}
