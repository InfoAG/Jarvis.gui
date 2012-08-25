#ifndef QMLMODULE_H
#define QMLMODULE_H

#include "Module.h"
#include <QObject>

class QMLModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)

private:
    Module moduleData;

public:
    QMLModule(const Module &module) : moduleData(module) {}

    QString name() const { return moduleData.name; }
    QString description() const { return moduleData.description; }
};

#endif // QMLMODULE_H
