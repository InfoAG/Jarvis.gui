#ifndef QMLFUNCTIONDEFINITION_H
#define QMLFUNCTIONDEFINITION_H

#include <QObject>
#include <QPair>
#include <QStringList>
#include "FunctionSignature.h"
#include "FunctionDefinition.h"

class QMLFunctionDefinition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier)
    Q_PROPERTY(QStringList argumentTypes READ argumentTypes)
    Q_PROPERTY(QString definition READ definition)
    Q_PROPERTY(QString returnType READ returnType)
    Q_PROPERTY(QStringList argumentNames READ argumentNames)


private:
    FunctionSignature signature_;
    FunctionDefinition definition_;

public:
    QMLFunctionDefinition(const FunctionSignature &key, const FunctionDefinition &value) : signature_(key),definition_(value) {};

    QString identifier() const { return signature_.identifier; }
    QStringList argumentTypes() const { return signature_.argumentTypes; }
    QString definition() const { return definition_.definition; }
    QString returnType() const { return definition_.returnType; }
    QStringList argumentNames() const { return definition_.argumentNames; }
};

#endif // QMLFUNCTIONDEFINITION_H
