#ifndef QMLVARIABLEDEFINITION_H
#define QMLVARIABLEDEFINITION_H


#include <QObject>
#include <QPair>
#include <QStringList>

class QMLVariableDefinition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier)
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString definition READ definition)

private:
    QString identifier_;
    QString type_;
    QString definition_;

public:
    QMLVariableDefinition(const QString &key, const QPair<QString, QString> &value) : identifier_(key), type_(value.first), definition_(value.second){};


    QString identifier() const { return identifier_; }
    QString type() const { return type_; }
    QString definition() const { return definition_; }
};

#endif // QMLVARIABLEDEFINITION_H
