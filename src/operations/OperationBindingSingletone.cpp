// self
#include "OperationBindingSingletone.h"

// operations
#include "CreateProjectOperation.h"
#include "SkipOperation.h"
#include "ExtractOperation.h"
#include "MakedirOperation.h"
#include "SystemOperation.h"
#include "InitProjectOperation.h"
#include "EnvOperation.h"

#include <QTextStream>

const QString stamp::OperationBindingSingletone::DEFAULT_OPERATION = "skip";

stamp::OperationBindingSingletone& stamp::OperationBindingSingletone::getInstance() {
  static OperationBindingSingletone instance;
  return instance;
}

stamp::Operation* stamp::OperationBindingSingletone::operation(const QString& operationName) {

  Operations::Iterator it = mOperations.find(operationName);

  Q_ASSERT_X(mOperations.contains(DEFAULT_OPERATION), __FUNCTION__,
             "Default operation must be in container");

  return (it != mOperations.end()) ? it.value() : mOperations[DEFAULT_OPERATION];
}

stamp::OperationBindingSingletone::OperationBindingSingletone()
: mOperations() {
  mOperations.insert("create", new stamp::CreateProjectOperation());
  mOperations.insert("skip", new stamp::SkipOperation());
  mOperations.insert("extract", new stamp::ExtractOperation());
  mOperations.insert("makedir", new stamp::MakedirOperation());
  mOperations.insert("system", new stamp::SystemOperation());
  mOperations.insert("init", new stamp::InitProjectOperation());
  mOperations.insert("env", new stamp::EnvOperation());
}

stamp::OperationBindingSingletone::~OperationBindingSingletone() {
  for (Operations::Iterator it = mOperations.begin(); it != mOperations.end(); ++it) {
    stamp::Operation* operation = (*it);
    delete operation;
    *it = nullptr;
  }
  mOperations.clear();
}

// TODO: replace recursion with queue
void stamp::OperationBindingSingletone::executeScript(const QStringList& script) {

  QTextStream out(stdout);

  for (QStringList::ConstIterator it = script.begin(); it != script.end(); ++it) {
    const QString& actionLine = (*it);

    out << actionLine << Qt::endl;


    QStringList splittedArguments = stamp::Operation::escapeSplit(actionLine);

    if ( ! splittedArguments.isEmpty()) {
      QString actionName = splittedArguments.at(ActionIndex);
      splittedArguments.pop_front(); // pop operation name

      stamp::Operation* currentOperation = this->operation(actionName);
      currentOperation->tryExecute(splittedArguments);
    }
  }
}
