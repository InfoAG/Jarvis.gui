#ifndef QMLFUNCTIONMODULE_H
#define QMLFUNCTIONMODULE_H

#include "FunctionModule.h"

class QMLFunctionModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(bool staticMatches READ staticMatches)
    Q_PROPERTY(QString matchString READ matchString)
    Q_PROPERTY(unsigned int matchArgCount READ matchArgCount)
    Q_PROPERTY(bool staticPriority READ staticPriority)
    Q_PROPERTY(unsigned int priority READ priority)

private:
    FunctionModule funcModuleData;

public:
    QMLFunctionModule(const FunctionModule &module) : funcModuleData(module) {};

    QString name() const { return funcModuleData.name; }
    QString description() const { return funcModuleData.description; }
    bool staticMatches() const { return funcModuleData.matches != nullptr; }
    QString matchString() const { return funcModuleData.matches->first; }
    unsigned int matchArgCount() const { return funcModuleData.matches->second; }
    bool staticPriority() const { return funcModuleData.priority.first; }
    unsigned int priority() const { return funcModuleData.priority.second; }
};

#endif // QMLFUNCTIONMODULE_H
