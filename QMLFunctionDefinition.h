#ifndef QMLFUNCTIONDEFINITION_H
#define QMLFUNCTIONDEFINITION_H

#include <QObject>
#include <QPair>
#include <QStringList>

class QMLFunctionDefinition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier)
    Q_PROPERTY(QStringList arguments READ arguments)
    Q_PROPERTY(QString definition READ definition)

private:
    QString identifier_, definition_;
    QStringList arguments_;

public:
    QMLFunctionDefinition(const QString &key, const QPair<QStringList, QString> &value) : identifier_(key),
        definition_(value.second), arguments_(value.first) {};

    QString identifier() const { return identifier_; }
    QStringList arguments() const { return arguments_; }
    QString definition() const { return definition_; }
};

#endif // QMLFUNCTIONDEFINITION_H
