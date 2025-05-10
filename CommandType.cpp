#include "CommandType.h"

const unordered_set<string> CommandType::CommandsWithArgument = { "echo", "wc", "tr", "head", "batch" };
const unordered_set<string> CommandType::CommandsWithoutArgument = { "time", "date", "touch", "truncate", "rm" };
const unordered_set<string> CommandType::CommandsOpeningFile = { "truncate", "echo", "wc" };
const unordered_set<string> CommandType::CommandsWithOption = { "wc", "head" };
const unordered_set<string> CommandType::CommandsWithFile = { "truncate", "touch", "rm" };
const unordered_set<string> CommandType::CommandsWithoutFile = { "prompt", "time", "date" };
const unordered_set<string> CommandType::CommandsWithoutOutput = { "prompt", "rm", "truncate", "touch", "batch" };
const unordered_set<string> CommandType::AllCommands = { "prompt", "rm", "truncate", "touch", "wc", "echo", "date", "time", "tr", "head", "batch" };
const unordered_set<string> CommandType::CommandsWithMoreArguments = { "tr" };


bool CommandType::isCommandWithArgument(string commandName) {

    return (CommandsWithArgument.find(commandName) != CommandsWithArgument.end());
}

bool CommandType::isCommandOpeningFile(string commandName) {

    return (CommandsOpeningFile.find(commandName) != CommandsOpeningFile.end());
}

bool CommandType::isCommandWithOption(string commandName) {

    return (CommandsWithOption.find(commandName) != CommandsWithOption.end());
}

bool CommandType::isCommandWithoutArgument(string commandName) {

    return (CommandsWithoutArgument.find(commandName) != CommandsWithoutArgument.end());
}

bool CommandType::isCommandWithoutFile(string commandName) {

    return (CommandsWithoutFile.find(commandName) != CommandsWithoutFile.end());
}

bool CommandType::isCommandWithFile(string commandName) {

    return (CommandsWithFile.find(commandName) != CommandsWithFile.end());
}

bool CommandType::isCommandWithoutOutput(string commandName) {

    return (CommandsWithoutOutput.find(commandName) != CommandsWithoutOutput.end());
}

bool CommandType::CommandExists(string commandName) {

    return (AllCommands.find(commandName) != AllCommands.end());
}

bool CommandType::isCommandWithMoreArguments(string commandName) {

    return (CommandsWithMoreArguments.find(commandName) != CommandsWithMoreArguments.end());
}