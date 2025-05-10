#ifndef UNTITLED24_COMMAND_H
#define UNTITLED24_COMMAND_H
#include "Reader.h"
#include <string>
#include <unordered_set>
#include <iostream>
#include "ErrorChecker.h"
#include "Interpreter.h"
#include "Pipe.h"

using namespace std;

class Preparator;


//The Base Class
class Command {
    //Allows Preparator to acess private parts of the command.
    friend class Preparator;

public:
    //Default constructor
    Command(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    //Default virtual Destructor
    virtual ~Command() = default;

    virtual string execute() = 0;

    //Returns true if command has options, false otherwise.
    bool isCommandWithOption();

protected:

    //Set holding all the possible options our Command has.
    unordered_set<string> Options;

    //Holds the option if it exists, if not then it is an empty string.
    string option = "";

    //Holds the arguments, if they exist, otherwise empty vector.
    vector<string> arguments;

    //Holds the name of the file, if we are reading from the file.
    string inputFileName = "";

    string outputFileName = "";

};

class CommandTime : public Command {
public:
    CommandTime(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandTime() override = default;

    //Prints out the time.
    string execute() override;
};

class CommandDate : public Command {
public:
    CommandDate(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);
    ~CommandDate() override = default;

    //Prints out the date.
    string execute() override;
};

class CommandWc : public Command {
public:
    //Not default. It sets options in the Constructor.
    CommandWc(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandWc() override = default;

    //Counts words or characters, based on the option.
    string execute() override;

private:
    //Counts the words.
    int countWords();

    //Counts the characters.
    int countChars();
};

class CommandTouch : public Command {
public:
    CommandTouch(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandTouch() override = default;

    //Opens the file.
    string execute() override;

private:
    bool fileExists(const string& file);
};

class CommandEcho : public Command {
public:
    CommandEcho(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandEcho() override = default;

    //Prints out the argument of the command.
    string execute() override;
};

class CommandPrompt : public Command {
public:
    CommandPrompt(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandPrompt() override = default;

    string execute() override;
};

//Deletes the file with the given name.
class CommandRm : public Command {
public:
    CommandRm(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandRm() override = default;

    string execute() override;
};

//Deletes the content of the file with the given name.
class CommandTruncate : public Command {
public:
    CommandTruncate(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandTruncate() override = default;

    string execute() override;
};

//Changes 'what' with 'with'
class CommandTr : public Command {
public:
    CommandTr(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandTr() override = default;

    string execute() override;

private:
    string WhatWith(string& argument, const string& what, const string& with);
};

class CommandHead : public Command {
public:
    CommandHead(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandHead() override = default;

    string execute() override;
};

class CommandBatch : public Command {
public:
    CommandBatch(const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

    ~CommandBatch() override = default;

    string execute() override;

private:
    void executeCommand(string& command);
};

//Class used for making commands.
class CommandFactory {
public:
    //COmmandFactory is a Singleton. Returns the only instance of CommandFactory.
    static CommandFactory* Instance();

    ~CommandFactory() = default;

    //We pass it the signature of the command, and it makes an object of that specific command.
    //Static because it does not operate on the instance of the class.
    static Command* createCommand(const string& commandName, const string& option,
        const vector<string>& arguments, const string& inputFileName, const string& outputFileName);

protected:
    CommandFactory() = default;

};

#endif
