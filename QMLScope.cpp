#include "QMLScope.h"

QMLScope::QMLScope(const Scope &scope) : clients_(scope.clients)
{
    for (auto it = scope.variables.begin(); it != scope.variables.end(); ++it)
        variables_.insert(it.key(), it.value());
    for (auto it = scope.functions.begin(); it !=  scope.functions.end(); ++it)
        functions_ << new QMLFunctionDefinition(it.key(), it.value());
}
