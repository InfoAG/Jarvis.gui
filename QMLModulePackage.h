#ifndef QMLMODULEPACKAGE_H
#define QMLMODULEPACKAGE_H

#include <QDeclarativeListProperty>
#include "ModulePackage.h"
#include "QMLModule.h"
#include "QMLOperatorModule.h"
#include "QMLFunctionModule.h"

class QMLModulePackage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QDeclarativeListProperty<QMLModule> terminals READ terminals)
    Q_PROPERTY(QDeclarativeListProperty<QMLOperatorModule> operators READ operators)
    Q_PROPERTY(QDeclarativeListProperty<QMLFunctionModule> functions READ functions)

private:
    QString name_;
    QList<QMLModule*> terminals_;
    QList<QMLOperatorModule*> operators_;
    QList<QMLFunctionModule*> functions_;

public:
    QMLModulePackage(const ModulePackage &pkg);

    QString name() const { return name_; }
    QDeclarativeListProperty<QMLModule> terminals() { return QDeclarativeListProperty<QMLModule>(this, terminals_); }
    QDeclarativeListProperty<QMLOperatorModule> operators() { return QDeclarativeListProperty<QMLOperatorModule>(this, operators_); }
    QDeclarativeListProperty<QMLFunctionModule> functions() { return QDeclarativeListProperty<QMLFunctionModule>(this, functions_); }
};

#endif // QMLMODULEPACKAGE_H
