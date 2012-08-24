#ifndef QMLOPERATORMODULE_H
#define QMLOPERATORMODULE_H

#include "QMLModule.h"
#include "OperatorModule.h"

class QMLOperatorModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(bool staticMatches READ staticMatches)
    Q_PROPERTY(QString matches READ matches)
    Q_PROPERTY(bool staticPriority READ staticPriority)
    Q_PROPERTY(unsigned int priority READ priority)
    Q_PROPERTY(bool staticAssociativity READ staticAssociativity)
    Q_PROPERTY(AssociativityType associativity READ associativity)
    Q_ENUMS(AssociativityType)

private:
    OperatorModule opModuleData;

public:
    enum AssociativityType {
        LEFT,
        RIGHT
    };
    QMLOperatorModule(const OperatorModule &module) : opModuleData(module) {}

    QString name() const { return opModuleData.name; }
    QString description() const { return opModuleData.description; }
    bool staticMatches() const { return opModuleData.matches != nullptr; }
    QString matches() const { return *opModuleData.matches; }
    bool staticPriority() const { return opModuleData.priority.first; }
    unsigned int priority() const { return opModuleData.priority.second; }
    bool staticAssociativity() const { return opModuleData.associativity.first; }
    AssociativityType associativity() const { return static_cast<AssociativityType>(opModuleData.associativity.second); }
};

#endif // QMLOPERATORMODULE_H
