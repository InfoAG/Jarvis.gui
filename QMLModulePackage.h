#ifndef QMLMODULEPACKAGE_H
#define QMLMODULEPACKAGE_H

#include <QVariant>
#include "ModulePackage.h"
#include "QMLModule.h"
#include "QMLOperatorModule.h"
#include "QMLFunctionModule.h"

struct QMLModulePackage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QList<QObject*> terminals READ terminals)
    Q_PROPERTY(QList<QObject*> operators READ operators)
    Q_PROPERTY(QList<QObject*> functions READ functions)

public:
    QMLModulePackage() {}
    QMLModulePackage(const ModulePackage &pkg);

    QString name() const { return name_; }
    QList<QObject*> terminals() const { return terminals_; }
    QList<QObject*> operators() const { return operators_; }
    QList<QObject*> functions() const { return functions_; }

    QString name_;
    QList<QObject*> terminals_;
    QList<QObject*> operators_;
    QList<QObject*> functions_;
};

#endif // QMLMODULEPACKAGE_H
