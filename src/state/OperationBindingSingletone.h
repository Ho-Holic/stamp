#pragma once

#include "operations/Operation.h"
#include <QMap>

namespace stamp {

class OperationBindingSingletone {
public:
    typedef QMap<QString, Operation*> Operations;

public:
    enum Argument { ActionIndex,
        ArgumentSize };

public:
    OperationBindingSingletone();
    ~OperationBindingSingletone();
    Operation* operation(const QString& operationName);
    void executeScript(const QStringList& script);

private:
    Operations mOperations;

private:
    static const QString DEFAULT_OPERATION;
};

OperationBindingSingletone& operationBinding();

}
