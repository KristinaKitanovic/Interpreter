#ifndef UNTITLED24_PREPARATOR_H
#define UNTITLED24_PREPARATOR_H
#include "Command.h"
#include "CommandParams.h"
#include "CommandType.h"

class Command;
class CommandFactory;

//Class used for additional loading arguments if needed and forming a command.
class Preparator {
public:
    //Constructor.
    Preparator() = default;

    //Destructor. No need to delete Singletons (FileReader & CommandFactory)
    ~Preparator() = default;

    //Main function. Responsible for preparing everything for execution. Prepares command and parameters.
    //Returns command fully ready for execution.
    Command* prepareAndFormCommand(const CommandParams& params);

    //Sets parameters and opens the File for Reading if needed. Fetches Reader and CommandFactory as well.
    void setParams(const CommandParams& params);

private:

    //If fileName was passed, read the argument from the file. Prepares argument for execution.
    string loadArgumentFromFile();

    //Struct that saves the passed parameters from the Parser. Used for easier access to parameters.
    CommandParams params;

    //Pointer to a reader. Needed for possible reading from a file.
    FileReader* reader;

    //CommandFactory, needed to create the specific command, based on the passed commandName.
    CommandFactory* factory;
};
#endif
