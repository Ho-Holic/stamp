#ifndef STAMP_OPERATION_H
#define STAMP_OPERATION_H

// qt
#include <QPair>
#include <QStringList>

namespace stamp {

typedef QPair<QString, QString> ArgumentPair;
typedef QList<ArgumentPair> ArgumentPairList;

class Operation {
private:
    Q_DISABLE_COPY(Operation)
public:
    Operation();
    virtual ~Operation();

public:
    void tryExecute(const QStringList& arguments);

public:
    virtual void execute(const QStringList& arguments) = 0;
    virtual QStringList::size_type minimumArgumentCount() const = 0;
    virtual QString usageString() const = 0;

public:
    static QStringList escapeSplit(const QString& argString);
    static void splitArguments(const QStringList& arguments, ArgumentPairList& named, QStringList& noname);
};

}
#endif // STAMP_OPERATION_H
