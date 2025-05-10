#include "ParameterFormatter.h"

void ParameterFormatter::reformatArguments(vector<string>& arguments) {

    for (int i = 0; i < arguments.size(); i++) {
        //Remove the first quote.
        if (arguments[i][0] == '"') {
            arguments[i] = arguments[i].substr(1);
        }
        //Remove the last quote.
        //Necessary, in case the line was trimmed to 512.
        if (!arguments[i].empty() && arguments[i][arguments[i].length() - 1] == '"') {
            arguments[i] = arguments[i].substr(0, arguments[i].length() - 1);
        }
    }
}

void ParameterFormatter::reformatFileName(string& fileName) {
    if (!fileName.empty() && fileName[0] == '<') {
        fileName = fileName.substr(1);
    }
}

void ParameterFormatter::reformatOption(string& option) {
    if (!option.empty()) {
        option = option.substr(1);
    }
}

void ParameterFormatter::reformatParameters(CommandParams& params)
{
    reformatArguments(params.arguments);
    reformatOption(params.option);
    reformatFileName(params.inputFileName);
}