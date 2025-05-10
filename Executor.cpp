#include "Executor.h"


//By this point all the parameters are right, and command is ready. Just call execute and delete the command afterwards.
string Executor::executeCommand(Command* command) {

    return command->execute();
    delete command;
}