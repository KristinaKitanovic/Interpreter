#include "Writter.h"
#include <fstream>
#include <iostream>
using namespace std;

void Writter::write(string& outputFileName, const string& content)
{
    if (!outputFileName.empty() && outputFileName[1] == '>') return appendOutput(outputFileName, content);
    return overwriteOutput(outputFileName, content);
}

void Writter::appendOutput(string& outputFileName, const string& content) {

    //Initially output is set to cout.
    ostream* out = &cout;
    ofstream file;

    //id output filename was passed, rediret the output.
    if (!outputFileName.empty()) {
        //Remove '>' signs
        file.open(outputFileName.substr(2), std::ios::app);
        if (!file) {
            std::cerr << "Error: Cannot open file for appending " << std::endl;
            return;
        }
        //Redirected output.
        out = &file;
    }

    *out << content << endl;

    if (file.is_open()) {
        file.close();
    }
}

void Writter::overwriteOutput(string& outputFileName, const string& content)
{

    ostream* out = &cout;
    std::ofstream file;

    if (!outputFileName.empty()) {
        //Remove '>' sign
        file.open(outputFileName.substr(1), std::ios::out | std::ios::trunc);
        if (!file) {
            std::cerr << "Error: Cannot open file for writing " << std::endl;
            return;
        }
        out = &file;
    }

    *out << content << endl;
    ;

    if (file.is_open()) {
        file.close();
    }
}