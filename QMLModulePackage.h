#ifndef QMLMODULEPACKAGE_H
#define QMLMODULEPACKAGE_H

#include <QDeclarativeListProperty>
#include "ModulePackage.h"
#include "QMLModule.h"
#include "QMLBinaryOperatorModule.h"
#include "QMLUnaryOperatorModule.h"
#include "QMLFunctionModule.h"

class QMLModulePackage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QDeclarativeListProperty<QMLModule> terminals READ terminals)
    Q_PROPERTY(QDeclarativeListProperty<QMLUnaryOperatorModule> unaryOperators READ unaryOperators)
    Q_PROPERTY(QDeclarativeListProperty<QMLBinaryOperatorModule> binaryOperators READ binaryOperators)
    Q_PROPERTY(QDeclarativeListProperty<QMLFunctionModule> functions READ functions)

private:
    QString name_;
    QList<QMLModule*> terminals_;
    QList<QMLBinaryOperatorModule*> binoperators_;
    QList<QMLUnaryOperatorModule*> unoperators_;

    QList<QMLFunctionModule*> functions_;

public:
    QMLModulePackage(const ModulePackage &pkg);

    QString name() const { return name_; }
    QDeclarativeListProperty<QMLModule> terminals() { return QDeclarativeListProperty<QMLModule>(this, terminals_); }
    QDeclarativeListProperty<QMLBinaryOperatorModule> binaryOperators() { return QDeclarativeListProperty<QMLBinaryOperatorModule>(this, binoperators_); }
    QDeclarativeListProperty<QMLUnaryOperatorModule> unaryOperators() { return QDeclarativeListProperty<QMLUnaryOperatorModule>(this, unoperators_); }
    QDeclarativeListProperty<QMLFunctionModule> functions() { return QDeclarativeListProperty<QMLFunctionModule>(this, functions_); }
};

#endif // QMLMODULEPACKAGE_H
