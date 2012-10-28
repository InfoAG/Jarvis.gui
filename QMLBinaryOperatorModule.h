#ifndef QMLBINARYOPERATORMODULE_H
#define QMLBINARYOPERATORMODULE_H

#include "QMLModule.h"
#include "BinaryOperatorModule.h"

class QMLBinaryOperatorModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(bool staticMatches READ staticMatches)
    Q_PROPERTY(QString matches READ matches)
    Q_PROPERTY(bool staticPriority READ staticPriority)
    Q_PROPERTY(unsigned int priority READ priority)
    Q_PROPERTY(AssociativityType associativity READ associativity)
    Q_ENUMS(AssociativityType)

private:
    BinaryOperatorModule opModuleData;

public:
    enum AssociativityType {
        LEFT,
        RIGHT
    };
    QMLBinaryOperatorModule(const BinaryOperatorModule &module) : opModuleData(module) {}

    QString name() const { return opModuleData.name; }
    QString description() const { return opModuleData.description; }
    bool staticMatches() const { return opModuleData.matches != nullptr; }
    QString matches() const { return *opModuleData.matches; }
    bool staticPriority() const { return opModuleData.priority.first; }
    unsigned int priority() const { return opModuleData.priority.second; }
    AssociativityType associativity() const { return static_cast<AssociativityType>(opModuleData.associativity); }
};

#endif // QMLBINARYOPERATORMODULE_H
