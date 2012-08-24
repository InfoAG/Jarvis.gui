#include "QMLModulePackage.h"
#include <QDebug>

QMLModulePackage::QMLModulePackage(const ModulePackage &pkg) : name_(pkg.name)
{
    std::transform(pkg.terminals.begin(), pkg.terminals.end(), std::back_inserter(terminals_), [](const Module &item) {
            return new QMLModule(item);
        });
    std::transform(pkg.operators.begin(), pkg.operators.end(), std::back_inserter(operators_), [](const OperatorModule &item) {
            return new QMLOperatorModule(item);
        });
    std::transform(pkg.functions.begin(), pkg.functions.end(), std::back_inserter(functions_), [](const FunctionModule &item) {
            return new QMLFunctionModule(item);
        });
}
