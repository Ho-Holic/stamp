#pragma once

#include "Operation.h"

namespace stamp {

class InitProjectOperation : public Operation {
public:
    enum Argument {
        InitDirPathIndex, // init project in this path
        ArgumentSize
    };

public:
    InitProjectOperation();

public:
    void execute(const QStringList& arguments) override;
    QStringList::size_type minimumArgumentCount() const override;
    QString usageString() const override;
};
}
