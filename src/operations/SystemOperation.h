#pragma once

#include "Operation.h"

namespace stamp {

class SystemOperation : public Operation {
public:
    enum Argument {
        SystemCommandIndex, // system command to run
        ArgumentSize
    };

public:
    SystemOperation();
    virtual void execute(const QStringList& arguments);
    virtual QStringList::size_type minimumArgumentCount() const;
    virtual QString usageString() const;
};
}
