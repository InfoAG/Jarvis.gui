#ifndef QMLMODULEPACKAGE_H
#define QMLMODULEPACKAGE_H

#include <QVariant>

struct QMLModulePackage
{
    QVariant name;
    QVariant terminals;
    QVariant operators;
    QVariant functions;
};

#endif // QMLMODULEPACKAGE_H
