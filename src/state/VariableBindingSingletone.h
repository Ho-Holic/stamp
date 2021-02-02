#pragma once

#include <QMap>
#include <QString>
#include <QStringList>

namespace stamp {

class VariableBindingSingletone {
public:
    typedef QMap<QString, QString> Variables;

public:
    VariableBindingSingletone();

public:
    void replaceVariablesIn(QStringList& source) const;
    void replaceVariablesIn(QString& source) const;
    void set(const QString& key, const QString& value);
    const Variables& variables() const;

private:
    Variables mVariables;
};

VariableBindingSingletone& variableBindings();

}
