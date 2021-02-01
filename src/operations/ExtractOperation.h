#ifndef STAMP_EXTRACT_OPERATION_H
#define STAMP_EXTRACT_OPERATION_H

// self
#include "Operation.h"

namespace stamp {

class ExtractOperation : public Operation {
public:
    enum Argument {
        ResourceFilePathIndex, // source qrc file to copy
        SaveFilePathIndex, // destination path for qrc file
        ArgumentSize
    };

public:
    ExtractOperation();

public:
    virtual void execute(const QStringList& arguments);
    virtual QStringList::size_type minimumArgumentCount() const;
    virtual QString usageString() const;
};
}

#endif // STAMP_EXTRACT_OPERATION_H
