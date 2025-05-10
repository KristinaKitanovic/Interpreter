#ifndef PARAMETERFORMATTER_H
#define PARAMETERFORMATTER_H
#include <string>
#include <vector>
#include "CommandParams.h"

using namespace std;

//Class used for formatting the parameters from the input.
//Puts them in the format the command expects for execution.
class ParameterFormatter {
public:
    ParameterFormatter() = default;
    ~ParameterFormatter() = default;

    //Main function. Calls reformat functions for all the parameters.
    void reformatParameters(CommandParams& params);

private:
    //Removes quotes form the beginning and the end of the argument if they exist.
    void reformatArguments(vector<string>& v);

    //Removes '<' if it exists.
    void reformatFileName(string& fileName);

    //Removes '-' from the option.
    void reformatOption(string& option);
};
#endif