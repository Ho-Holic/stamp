#ifndef STAMP_CREATE_PROJECT_OPERATION_H
#define STAMP_CREATE_PROJECT_OPERATION_H

// self
#include "VariableBindingSingletone.h"
#include "Operation.h"

// qt
#include <QString>
#include <QMap>

namespace stamp {

  class CreateProjectOperation : public Operation {
  public:

    enum Argument { 
      ModuleTypeIndex,  // module position
      ProjectNameIndex, // project name position
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

#endif // STAMP_CREATE_PROJECT_OPERATION_H
