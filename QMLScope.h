#ifndef QMLSCOPE_H
#define QMLSCOPE_H

#include <QDeclarativeListProperty>
#include <QMap>
#include <QString>
#include "Scope.h"
#include <QVariantMap>
#include "QMLFunctionDefinition.h"

class QMLScope : public QObject
{   
    Q_OBJECT
    Q_PROPERTY(QStringList clients READ clients)
    Q_PROPERTY(QVariantMap variables READ variables)
    Q_PROPERTY(QDeclarativeListProperty<QMLFunctionDefinition> functions READ functions)

private:
    QStringList clients_;
    QVariantMap variables_;
    QList<QMLFunctionDefinition*> functions_;

public:
    QMLScope(const Scope &scope);

    QStringList clients() const { return clients_; }
    QVariantMap variables() const { return variables_; }
    QDeclarativeListProperty<QMLFunctionDefinition> functions() { return QDeclarativeListProperty<QMLFunctionDefinition>(this, functions_); }
};

#endif // QMLSCOPE_H
