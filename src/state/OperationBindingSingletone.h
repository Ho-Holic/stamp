#pragma once

#include "operations/Operation.h"
#include <map>

namespace stamp {

class OperationBindingSingletone {
public:
    enum Argument {
        ActionIndex,
        ArgumentSize
    };

public:
    OperationBindingSingletone();
    Operation* operation(const QString& operationName);
    void executeScript(const QStringList& script);

private:
    std::map<QString, std::shared_ptr<Operation>> m_operations;
};

OperationBindingSingletone& operationBinding();

}
