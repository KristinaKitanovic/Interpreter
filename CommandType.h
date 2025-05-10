#ifndef UNTITLED24_COMMANDTYPE_H
#define UNTITLED24_COMMANDTYPE_H
#include <string>
#include <unordered_set>
using namespace std;

class CommandType {
public:
    //Return true if Command has argument, false otherwise.
    static bool isCommandWithArgument(string commandName);

    //Return true if the command needs to open the file but is not reading from it.
    static bool isCommandOpeningFile(string commandName);

    //Returns true if the command has option, otherwise false
    static bool isCommandWithOption(string commandName);

    //Returns true if the command has no argument.
    static bool isCommandWithoutArgument(string commandName);

    //Returns true if the command must have file.
    static bool isCommandWithFile(string commandName);

    //Returns true if the command must not have file.
    static bool isCommandWithoutFile(string commandName);

    //Returns true if the command has no output.
    static bool isCommandWithoutOutput(string commandName);

    //Returns true if command exists.
    static bool CommandExists(string commandName);

    //Returns true if command exists.
    static bool isCommandWithMoreArguments(string commandName);




private:

    static const unordered_set<string> CommandsWithArgument;
    static const unordered_set<string> CommandsWithoutArgument;
    static const unordered_set<string> CommandsOpeningFile;
    static const unordered_set<string> CommandsWithOption;
    static const unordered_set<string> CommandsWithFile;
    static const unordered_set<string> CommandsWithoutFile;
    static const unordered_set<string> CommandsWithoutOutput;
    static const unordered_set<string> AllCommands;
    static const unordered_set<string> CommandsWithMoreArguments;


};

#endif