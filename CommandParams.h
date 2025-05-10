#ifndef UNTITLED24_COMMANDPARAMS_H
#define UNTITLED24_COMMANDPARAMS_H
#include <string>
using namespace std;

//Structure used to store all the parameters a command can have.
struct CommandParams
{
    string commandName;
    string option;
    vector<string> arguments;
    string inputFileName;
    string outputFileName;
};

#endif
