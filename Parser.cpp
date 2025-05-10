#include "Parser.h"
#include <string>
#include <iostream>
#include <unordered_set>

Parser::Parser()
{
    //Always reads lines from the standard input.
    reader = new InputStreamReader();
}

Parser::~Parser()
{
    delete reader;
}

void Parser::removeLeadingBlancos(string& line) {

    int firstNonSpace = line.find_first_not_of(" \t\n\r\f\v");

    if (firstNonSpace != std::string::npos) {
        line = line.substr(firstNonSpace);
    }
    else {

        line.clear();
    }
}

string Parser::extractFirstWord(string& line) {

    removeLeadingBlancos(line);

    //If the line is empty, return empty string
    if (line.empty())
    {
        return "";
    }
    string firstWord;
    int positionOfSpace = line.find(' ');

    //If there is no space in the line, the first word will be the only word in the line.
    if (positionOfSpace == string::npos)
    {
        firstWord = line;
        line = "";
    }
    else//If there is space in the line, the first word is until that space.
    {
        firstWord = line.substr(0, positionOfSpace);
        //New string is tarting with position positionOfSpace + 1 and goes until the end of the line.
        line = line.substr(positionOfSpace + 1);

    }
    return firstWord;
}

void Parser::TrimTo512(string& line)
{
    if (line.length() > 512)
    {
        line = line.substr(0, 512);
    }

}

void Parser::cleanParams(CommandParams& params)
{
    params.arguments.clear();
    params.option.clear();
    params.inputFileName.clear();
    params.outputFileName.clear();
    params.commandName.clear();
}

bool Parser::representsInputFileName(string& line) {
    removeLeadingBlancos(line);
    //The rest of the line represents th fileName if its not empty and it does not start with quotes.
    return (!line.empty() && line[0] != '"' && line[0] != '>' && line[0] != '-');
}

bool Parser::representsOutputFileName(string& line) {
    removeLeadingBlancos(line);
    return (!line.empty() && line[0] == '>');
}

bool Parser::representsArgument(string& line) {
    removeLeadingBlancos(line);
    return (!line.empty() && line[0] == '\"');
}


bool Parser::representsOption(string& line) {
    removeLeadingBlancos(line);
    //The next part of the line represents the option if it starts with minus(-) and if it is not empty.
    return (!line.empty() && line[0] == '-');
}

void Parser::readOption(string& line) {

    params.option = extractFirstWord(line);
}

void Parser::readCommandName(string& line) {
    params.commandName = extractFirstWord(line);
}

void Parser::readArgument(string& line) {

    int StartingQuote = line.find('\"');
    int EndingQuote = line.find('\"', StartingQuote + 1);
    string argument = "";

    if (StartingQuote == EndingQuote)
    {
        argument = line;
        line = "";
    }
    else {
        argument = line.substr(StartingQuote, EndingQuote - StartingQuote + 1);
        line = line.substr(EndingQuote + 1);
    }

    string previousLine = "";

    // If line is empty and our command is the command that has an argument, read the rest of the lines below.
    if (argument.empty() && commandType.isCommandWithArgument(params.commandName) && params.inputFileName.empty()) {

        while (true) {
            line = reader->getNextLine();

            // Stop when EOF is entered.
            if (reader->endOfRead()) break;

            TrimTo512(line);

            if (line.empty())
            {
                argument += '\n';
            }
            if (!previousLine.empty())
            {
                argument += '\n';
            }

            argument += line;
            previousLine = line;
        }
    }
    if (!argument.empty())
        params.arguments.push_back(argument);
}

void Parser::readInputFileName(string& line) {


    params.inputFileName = extractFirstWord(line);
    if (params.inputFileName.length() == 1 && params.inputFileName[0] == '<')
    {
        params.inputFileName += extractFirstWord(line);
    }
}

void Parser::readOutputFileName(string& line) {


    params.outputFileName = extractFirstWord(line);
    if (params.outputFileName.length() == 1 && params.outputFileName[0] == '>' ||
        params.outputFileName.length() == 2 && params.outputFileName[0] == params.outputFileName[1] == '>') {
        params.outputFileName += extractFirstWord(line);
    }
}

void Parser::FindUnexpectedCharacters(string& line)
{
    unordered_set<int> Unexpected;
    int StartingQuote = line.find('\"');
    int EndingQuote = line.rfind('\"');

    for (int i = 0; i < line.length(); i++)
    {
        if ((line[i] == '^' || line[i] == '@' || line[i] == '%' ||
            line[i] == '!' || line[i] == '*' || line[i] == '?' ||
            line[i] == '&' || line[i] == ')' || line[i] == '(') &&
            ((StartingQuote == std::string::npos && EndingQuote == std::string::npos) ||
                (StartingQuote != EndingQuote && (i < StartingQuote || i > EndingQuote)) ||
                (StartingQuote == EndingQuote && i < EndingQuote)))
            Unexpected.insert(i);
    }
    if (!Unexpected.empty()) throw UnexpectedCharacters(line, Unexpected);
}

void Parser::checkForBadInput(string& line)
{
    removeLeadingBlancos(line);

    if (!line.empty() && line[0] == '-')
        throw TooManyOptions();
    else if (!line.empty() && line[0] == '>')
        throw TooManyOutputFiles();
    else if (!line.empty() && line[0] == '"' && (!params.outputFileName.empty() || !params.inputFileName.empty()))
        throw InputAfterFile();
    else if (!line.empty() && line[0] == '"')
        throw TooManyArguments();
    else if (!line.empty())
        throw TooManyInputFiles();

    if (!CommandType::CommandExists(params.commandName)) throw InvalidCommandError(params.commandName);

    //Check whether parameters are correct for the given command
    if (!params.option.empty() && !CommandType::isCommandWithOption(params.commandName)) throw HasCommand();
    if (params.option.empty() && CommandType::isCommandWithOption(params.commandName)) throw NoCommand();
    if (!params.arguments.empty() && CommandType::isCommandWithoutArgument(params.commandName)) throw HasArgument();
    if (!params.inputFileName.empty() && CommandType::isCommandWithoutFile(params.commandName)) throw HasFile();
    if (!params.outputFileName.empty() && CommandType::isCommandWithoutOutput(params.commandName)) throw HasRedirectedOutput();
    if (params.inputFileName.empty() && CommandType::isCommandWithFile(params.commandName)) throw NoFile();
    if (!params.inputFileName.empty() && !params.arguments.empty()) throw HasBothArgumentAndInputFile();

}

void Parser::read(string& line) {

    FindUnexpectedCharacters(line);
    readCommandName(line);
    if (representsOption(line)) {

        readOption(line);
    }
    while (representsArgument(line) && (params.arguments.empty() || CommandType::isCommandWithMoreArguments(params.commandName)))
    {
        readArgument(line);
    }
    if (representsInputFileName(line)) {

        readInputFileName(line);

    }
    if (representsOutputFileName(line)) {

        readOutputFileName(line);

    }
    if (representsInputFileName(line) && params.inputFileName.empty()) {

        readInputFileName(line);
    }

    if ((params.arguments.empty() && line.empty() && CommandType::isCommandWithArgument(params.commandName)))
        readArgument(line);

    checkForBadInput(line);
}

CommandParams Parser::parse(string& line, string argument)
{
    //Clean up params from the previous iteration.
    cleanParams(params);
    if (!argument.empty()) params.arguments.push_back(argument);

    //Fill params with new parameters.
    read(line);
    return params;
}
