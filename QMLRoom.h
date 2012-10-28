#ifndef QMLROOM_H
#define QMLROOM_H

#include <QDeclarativeListProperty>
#include <QMap>
#include <QString>
#include <QPair>
#include "Room.h"
#include "QMLFunctionDefinition.h"
#include "QMLVariableDefinition.h"
#include "FunctionSignature.h"

class QMLRoom : public QObject
{   
    Q_OBJECT
    Q_PROPERTY(QStringList clients READ clients)
    Q_PROPERTY(QDeclarativeListProperty<QMLVariableDefinition> variables READ variables)
    Q_PROPERTY(QDeclarativeListProperty<QMLFunctionDefinition> functions READ functions)

private:
    QStringList clients_;
    QList<QMLFunctionDefinition*> functions_;
    QList<QMLVariableDefinition*> variables_;



public:
    QMLRoom(const Room &room);

    QStringList clients() const { return clients_; }
    QDeclarativeListProperty<QMLVariableDefinition> variables() { return QDeclarativeListProperty<QMLVariableDefinition>(this, variables_); }
    QDeclarativeListProperty<QMLFunctionDefinition> functions() { return QDeclarativeListProperty<QMLFunctionDefinition>(this, functions_); }
};

#endif // QMLROOM_H
