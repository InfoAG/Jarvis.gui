#ifndef QMLSCOPE_H
#define QMLSCOPE_H

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
    Q_PROPERTY(QList<QObject*> functions READ functions)

private:
    QStringList clients_;
    QVariantMap variables_;
    QList<QObject*> functions_;

public:
    QMLScope(const Scope &scope);

    QStringList clients() const { return clients_; }
    QVariantMap variables() const { return variables_; }
    QList<QObject*> functions() const { return functions_; }
};

typedef QMap<QString, QString> VarDefs;
typedef QMap<QString, QPair<QStringList, QString>> FuncDefs;

#endif // QMLSCOPE_H
