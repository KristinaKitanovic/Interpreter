
#ifndef UNTITLED24_EXECUTOR_H
#define UNTITLED24_EXECUTOR_H
#include "Command.h"

class Command;

//Class used for executing commands and deleting them afterwards.
class Executor {
public:
    Executor() = default;
    ~Executor() = default;

    //Executes command by calling the execute method for the specific command.
    static string executeCommand(Command* command);
};
#endif