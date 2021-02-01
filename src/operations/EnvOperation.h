#pragma once

#include "Operation.h"

namespace stamp {

class EnvOperation : public Operation {
public:
    EnvOperation();
public:
    void execute(const QStringList& arguments) override;
    QStringList::size_type minimumArgumentCount() const override;
    QString usageString() const override;
};
}
