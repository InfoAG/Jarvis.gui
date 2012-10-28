#include "QMLModulePackage.h"
#include <QDebug>

QMLModulePackage::QMLModulePackage(const ModulePackage &pkg) : name_(pkg.name)
{
    std::transform(pkg.terminals.begin(), pkg.terminals.end(), std::back_inserter(terminals_), [](const Module &item) {
            return new QMLModule(item);
        });
    std::transform(pkg.binaryOperators.begin(), pkg.binaryOperators.end(), std::back_inserter(binoperators_), [](const BinaryOperatorModule &item) {
            return new QMLBinaryOperatorModule(item);
        });
    std::transform(pkg.unaryOperators.begin(), pkg.unaryOperators.end(), std::back_inserter(unoperators_), [](const UnaryOperatorModule &item) {
            return new QMLUnaryOperatorModule(item);
        });
    std::transform(pkg.functions.begin(), pkg.functions.end(), std::back_inserter(functions_), [](const FunctionModule &item) {
            return new QMLFunctionModule(item);
        });
}
