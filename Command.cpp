#include "Command.h"
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <filesystem>
using namespace std;

Command::Command(const string& option,
    const vector<string>& arguments, const string& inputFileName, const string& outputFileName) {
    this->option = option;
    this->arguments = arguments;
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
}

bool Command::isCommandWithOption() {
    //Returns true if Options set for command is not empty.
    return (!Options.empty());
}

CommandTime::CommandTime(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandDate::CommandDate(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandEcho::CommandEcho(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandTouch::CommandTouch(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandPrompt::CommandPrompt(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandTruncate::CommandTruncate(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandRm::CommandRm(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandTr::CommandTr(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandHead::CommandHead(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}

CommandBatch::CommandBatch(const string& option, const vector<string>& arguments, const string& inputFileName, const string& outputFileName)
    : Command(option, arguments, inputFileName, outputFileName) {}


CommandWc::CommandWc(const string& option,
    const vector<string>& arguments, const string& inputFileName, const string& outputFileName) : Command(option, arguments, inputFileName, outputFileName) {
    //insert all the possible options for the command.
    Options = { "w", "c" };
}

int CommandWc::countChars() {
    int charCounter = 0;
    char prevChar = '\0';
    for (char currChar : arguments[0]) {
        if (!(currChar == '\n' && prevChar != '\n')) charCounter++;

        prevChar = currChar;
    }
    return charCounter;
}

int CommandWc::countWords() {
    int wordCount = 0;
    int start = 0, end;

    //Find the start of the word.
    while (start < arguments[0].length() && isspace(arguments[0][start]))
    {
        start++;
    }
    while (start < arguments[0].length()) {
        // Find the ending of the word.
        int end = arguments[0].find_first_of(" \t\n\r\f\v", start);
        if (end == string::npos) {
            wordCount++;
            break;
        }
        wordCount++;
        start = end;
        while (start < arguments[0].length() && isspace(arguments[0][start])) {
            start++;
        }
    }
    return wordCount;
}

string CommandTime::execute() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm local_time;
    localtime_s(&local_time, &now_time);// Safe version for Windows

    string content =
        (local_time.tm_hour < 10 ? "0" : "") + to_string(local_time.tm_hour) + ":" +
        (local_time.tm_min < 10 ? "0" : "") + to_string(local_time.tm_min) + ":" +
        (local_time.tm_sec < 10 ? "0" : "") + to_string(local_time.tm_sec);
    return content;
}

string CommandDate::execute() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm local_time;
    localtime_s(&local_time, &now_time);// Safe version for Windows

    string content =
        to_string(local_time.tm_year + 1900) + "-" +
        (local_time.tm_mon + 1 < 10 ? "0" : "") + to_string(local_time.tm_mon + 1) + "-" +
        (local_time.tm_mday < 10 ? "0" : "") + to_string(local_time.tm_mday);

    return content;
}


string CommandEcho::execute() {

    return arguments[0];
}

string CommandWc::execute() {
    int counter = 0;
    if (option == "w") {
        counter = countWords();
        return "Number of words: " + to_string(counter);
    }
    else if (option == "c") {
        counter = countChars();
        return "Number of characters: " + to_string(counter);
    }
    throw BadOption();
}

string CommandHead::execute() {
    if (option[0] != 'n' || option.length() > 6) throw BadOption();
    int numOfLines = atoi(option.substr(1).c_str());
    int i = 0, count = 0;
    string result = "";
    while (i < arguments[0].length()) {

        result += arguments[0][i];
        if (arguments[0][i] == '\n') {
            count++;
            if (count == numOfLines) break;
        }
        i++;

    }
    return result;
}

void CommandBatch::executeCommand(string& command)
{
    try {
        Pipe::execute(command);
    }
    catch (exception& e) {
        cout << e.what();
    }
}

string CommandBatch::execute() {

    string command = "";
    for (char c : arguments[0])
    {
        if (c == '\n') {
            executeCommand(command);
            command.clear();
        }
        else {
            command += c;
        }

    }
    executeCommand(command);
    return "";
}

bool CommandTouch::fileExists(const string& fileName)
{
    ifstream file(fileName);
    return (file.good());
}

string CommandTouch::execute() {
    if (fileExists(inputFileName))
    {
        throw FileAlreadyExistsError();
    }
    ofstream newFile(inputFileName);

    if (!newFile) {
        cout << "Error creating the file: " << inputFileName << endl;
    }
    else {
        cout << "File successfully created" << endl;
    }
    return "";
}

string CommandPrompt::execute() {

    Interpreter::Instance()->changeReadyNotifier(arguments[0]);
    return "";
}

string CommandRm::execute() {

    if (std::remove(inputFileName.c_str()) != 0) {
        std::perror("Error deleting file");
    }
    else {
        std::cout << "File deleted successfully." << std::endl;
    }
    return "";
}

string CommandTruncate::execute() {

    // Check if the file exists before trying to open it
    if (!std::filesystem::exists(inputFileName)) {
        throw FileDoesNotExistError();
    }

    // Open the file in truncation mode to clear its contents
    std::ofstream file(inputFileName, std::ios::out | std::ios::trunc);

    if (!file) {
        std::cerr << "Error: Cannot open the file to clear: " << inputFileName << std::endl;
        return "";
    }

    file.close();
    std::cout << "File content cleared successfully!" << std::endl;
    return "";
}

string CommandTr::WhatWith(string& argument, const string& what, const string& with)
{
    int pos = 0;

    while ((pos = argument.find(what, pos)) != std::string::npos) {
        argument.replace(pos, what.length(), with);
        pos += with.length();
    }
    return argument;
}

string CommandTr::execute() {

    if (!(arguments.size() == 3 || arguments.size() == 2)) throw WrongNumberOfArguments();
    if (arguments.size() == 3)
    {
        return WhatWith(arguments[0], arguments[1], arguments[2]);
    }
    else
        return WhatWith(arguments[0], arguments[1], "");
}

CommandFactory* CommandFactory::Instance() {
    static CommandFactory instance;
    return &instance;
}

Command* CommandFactory::createCommand(const string& commandName, const string& option,
    const vector<string>& arguments, const string& inputFileName, const string& outputFileName) {
    if (commandName == "time")
    {
        return new CommandTime(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "date")
    {
        return new CommandDate(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "wc")
    {
        return new CommandWc(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "touch")
    {
        return new CommandTouch(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "echo")
    {
        return new CommandEcho(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "prompt")
    {
        return new CommandPrompt(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "rm") {
        return new CommandRm(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "truncate") {
        return new CommandTruncate(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "tr") {
        return new CommandTr(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "head") {
        return new CommandHead(option, arguments, inputFileName, outputFileName);
    }
    if (commandName == "batch") {
        return new CommandBatch(option, arguments, inputFileName, outputFileName);
    }

    return nullptr;
}