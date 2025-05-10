#include "Preparator.h"
#include "Parser.h"

void Preparator::setParams(const CommandParams& newParams)
{
    params = newParams;

    //We will not form the FileReader or assign it the name of the file if there is no need or no fileName passed.
    //We will not try to open the file if that file is meant to be created and not read from.
    if (!params.inputFileName.empty() && CommandType::isCommandWithArgument(params.commandName)) {
        reader = FileReader::Instance(params.inputFileName);
    }
    else {
        reader = nullptr;
    }
    factory = CommandFactory::Instance();
}

string Preparator::loadArgumentFromFile() {
    //Read all the lines from the file and load them in the argument.
    string argument = "", line;
    string previousLine = "";
    while (true) {
        line = reader->getNextLine();
        Parser::TrimTo512(line);
        if (line.empty()) {
            argument += '\n';
        }
        if (!previousLine.empty()) {
            argument += '\n';
        }
        argument += line;
        previousLine = line;
        // Stop when EOF is entered.
        if (reader->endOfRead()) break;
    }
    return argument;
}

Command* Preparator::prepareAndFormCommand(const CommandParams& newParams)
{
    setParams(newParams);

    //If reader is not set to nullptr, then we have to read from file.
    if (reader)
    {
        params.arguments.push_back(loadArgumentFromFile());
    }
    //Create the specific command with passed parameters.
    Command* command = factory->createCommand(params.commandName, params.option,
        params.arguments, params.inputFileName, params.outputFileName);

    return command;
}
