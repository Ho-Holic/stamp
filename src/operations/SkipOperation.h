#ifndef STAMP_SKIP_OPERATION_H
#define STAMP_SKIP_OPERATION_H

// self
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

#endif // STAMP_SKIP_OPERATION_H
