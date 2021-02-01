#ifndef STAMP_OPERATION_BINDING_SINGLETONE_H
#define STAMP_OPERATION_BINDING_SINGLETONE_H

// qt
#include <QMap>

// self
#include "operations/Operation.h"

namespace stamp {

class OperationBindingSingletone {
public:
    typedef QMap<QString, Operation*> Operations;

public:
    enum Argument { ActionIndex,
        ArgumentSize };

public:
    static OperationBindingSingletone& getInstance();

public:
    Operation* operation(const QString& operationName);
    void executeScript(const QStringList& script);

private:
    OperationBindingSingletone();
    ~OperationBindingSingletone();

private:
    Operations mOperations;

private:
    static const QString DEFAULT_OPERATION;
};
}
#endif // STAMP_OPERATION_BINDING_SINGLETONE_H
