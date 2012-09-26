#ifndef QMLROOM_H
#define QMLROOM_H

#include <QDeclarativeListProperty>
#include <QMap>
#include <QString>
#include "Room.h"
#include <QVariantMap>
#include "QMLFunctionDefinition.h"

class QMLRoom : public QObject
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
    QMLRoom(const Room &room);

    QStringList clients() const { return clients_; }
    QVariantMap variables() const { return variables_; }
    QDeclarativeListProperty<QMLFunctionDefinition> functions() { return QDeclarativeListProperty<QMLFunctionDefinition>(this, functions_); }
};

#endif // QMLROOM_H
