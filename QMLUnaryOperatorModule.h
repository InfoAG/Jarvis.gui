#ifndef QMLUNARYOPERATORMODULE_H
#define QMLUNARYOPERATORMODULE_H

#include "QMLModule.h"
#include "UnaryOperatorModule.h"

class QMLUnaryOperatorModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(bool staticMatches READ staticMatches)
    Q_PROPERTY(QString matches READ matches)
    Q_PROPERTY(bool staticPriority READ staticPriority)
    Q_PROPERTY(unsigned int priority READ priority)
    Q_PROPERTY(AlignmentType alignment READ alignment)
    Q_ENUMS(AlignmentType)

private:
    UnaryOperatorModule opModuleData;

public:
    enum AlignmentType { PRE, POST, DYNAMIC };
    AlignmentType alignment_;
    QMLUnaryOperatorModule(const UnaryOperatorModule &module) : opModuleData(module) {}

    QString name() const { return opModuleData.name; }
    QString description() const { return opModuleData.description; }
    bool staticMatches() const { return opModuleData.matches != nullptr; }
    QString matches() const { return *opModuleData.matches; }
    bool staticPriority() const { return opModuleData.priority.first; }
    unsigned int priority() const { return opModuleData.priority.second; }
    AlignmentType alignment() const { return static_cast<AlignmentType>(opModuleData.alignment); }
};

#endif // QMLUNARYOPERATORMODULE_H
