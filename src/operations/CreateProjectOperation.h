#pragma once

#include "Operation.h"
#include "state/VariableBindingSingletone.h"
#include <QMap>
#include <QString>

namespace stamp {

class CreateProjectOperation : public Operation {
public:
    enum Argument {
        TemplateNameIndex, // name of template folder to use
        TargetPathIndex, // where to copy processed template
        ArgumentSize
    };

public:
    CreateProjectOperation();

public:
    virtual void execute(const QStringList& arguments);
    virtual QStringList::size_type minimumArgumentCount() const;
    virtual QString usageString() const;

private:
    void processNamedArguments(const stamp::ArgumentPairList& namedArguments);
};
}
