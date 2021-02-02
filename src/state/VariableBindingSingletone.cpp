#include "VariableBindingSingletone.h"

stamp::VariableBindingSingletone& stamp::variableBindings()
{
    static VariableBindingSingletone instance;
    return instance;
}

stamp::VariableBindingSingletone::VariableBindingSingletone()
    : mVariables()
{
    //
}

void stamp::VariableBindingSingletone::replaceVariablesIn(QStringList& source) const
{
    for (QStringList::Iterator i = source.begin(); i != source.end(); ++i) {
        QString& stringSource = (*i);
        replaceVariablesIn(stringSource);
    }
}

void stamp::VariableBindingSingletone::replaceVariablesIn(QString& source) const
{

    for (Variables::ConstIterator i = mVariables.begin(); i != mVariables.end(); ++i) {
        source.replace(i.key(), i.value(), Qt::CaseSensitive);
    }
}

void stamp::VariableBindingSingletone::set(const QString& key, const QString& value)
{
    mVariables.insert(key, value);
}

const stamp::VariableBindingSingletone::Variables& stamp::VariableBindingSingletone::variables() const
{
    return mVariables;
}
