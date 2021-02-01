#ifndef STAMP_VARIABLE_BINDING_H
#define STAMP_VARIABLE_BINDING_H

// qt
#include <QMap>
#include <QString>
#include <QStringList>

namespace stamp {

  class VariableBindingSingletone {
  public:
    typedef QMap<QString, QString> Variables;

  public:
    static VariableBindingSingletone& getInstance();

  private:
    VariableBindingSingletone();

  public:
    void replaceVariablesIn(QStringList& source) const;
    void replaceVariablesIn(QString& source) const;
    void set(const QString& key, const QString& value);
    const Variables& variables() const;

  private:
    Variables mVariables;
  };
}
#endif // STAMP_VARIABLE_BINDING_H
