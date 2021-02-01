#ifndef STAMP_MAKEDIR_OPERATION_H
#define STAMP_MAKEDIR_OPERATION_H

#include "Operation.h"

namespace stamp {

class MakedirOperation : public Operation {
public:
    enum Argument {
        CreateDirPathIndex, // path to create dir
        ArgumentSize
    };

public:
    MakedirOperation();

public:
    virtual void execute(const QStringList& arguments);
    virtual QStringList::size_type minimumArgumentCount() const;
    virtual QString usageString() const;
};
}

#endif // STAMP_MAKEDIR_OPERATION_H
