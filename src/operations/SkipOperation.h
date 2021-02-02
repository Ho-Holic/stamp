#pragma once

#include "Operation.h"

namespace stamp {

class SkipOperation : public Operation {
public:
    SkipOperation();
    virtual void execute(const QStringList& arguments);
    virtual QStringList::size_type minimumArgumentCount() const;
    virtual QString usageString() const;
};

}
