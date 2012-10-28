#ifndef QMLFUNCTIONDEFINITION_H
#define QMLFUNCTIONDEFINITION_H

#include <QObject>
#include <QPair>
#include <QStringList>
#include "FunctionSignature.h"

class QMLFunctionDefinition : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString identifier READ identifier)
    Q_PROPERTY(QStringList arguments READ arguments)
    Q_PROPERTY(QString definition READ definition)

private:
    FunctionSignature signature_;
    QStringList arguments_;
    QString definition_;

public:
    QMLFunctionDefinition(const FunctionSignature &key, const QPair<QStringList, QString> &value) : signature_(key),
        arguments_(value.first), definition_(value.second) {};

    //QString identifier() const { return identifier_; }
    QStringList arguments() const { return arguments_; }
    QString definition() const { return definition_; }
};

#endif // QMLFUNCTIONDEFINITION_H
