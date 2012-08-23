#ifndef QMLSCOPE_H
#define QMLSCOPE_H

#include <QVariant>
#include <QMetaType>

struct QMLScope
{   
    QMLScope(const QStringList &clients, const QMap<QString, QString> &variables,
             const QMap<QString, QPair<QStringList, QString>> &functions)
        : clients(QVariant::fromValue(clients)), variables(QVariant::fromValue(variables)),
          functions(QVariant::fromValue(functions)) {}

    QVariant clients;
    QVariant variables;
    QVariant functions;
};

Q_DECLARE_METATYPE(QMLScope)
Q_DECLARE_METATYPE(QMap<QString, QString>)
Q_DECLARE_METATYPE(QMap<QString, QPair<QStringList, QString>>)

#endif // QMLSCOPE_H
