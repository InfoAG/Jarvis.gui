#include "QMLRoom.h"

QMLRoom::QMLRoom(const Room &room) : clients_(room.clients)
{
    for (auto it = room.variables.begin(); it != room.variables.end(); ++it)
        variables_.insert(it.key(), it.value());
    for (auto it = room.functions.begin(); it !=  room.functions.end(); ++it)
        functions_ << new QMLFunctionDefinition(it.key(), it.value());
}
