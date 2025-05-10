#ifndef PARSER_H
#define PARSER_H
#include "Reader.h"
#include "CommandParams.h"
#include "CommandType.h"


//Class Parser used for extracting parts of the input. Stores them in the struct CommandParams. 
class Parser {
public:
    friend class Preparator;

    Parser();

    ~Parser();

    //Main function of Class Parse. Simulates the whole process of parsing. 
    //Takes the result from previous command in the pipe and uses it as argument in the current command.
    CommandParams parse(string& line, string argument);

    //If the line is longer than 512 characters, trim to to 512.
    static void TrimTo512(string& line);

private:
    //Reads the command and extracts all the parts of the command.
    void read(string& line);

    //If next part of line represents the name of the file return true, otherwise return false.
    bool representsInputFileName(string& line);

    //If next part of line represents the name eof output file return true, else false
    bool representsOutputFileName(string& line);

    //If next part of line represents the option return true, otherwise return false.
    bool representsOption(string& line);

    bool representsArgument(string& line);

    //Extracts the name of the command. Passed by reference, changes the original.
    void readCommandName(string& line);

    //Extracts the option from the input. Passed by reference, changes the original.
    void readOption(string& line);

    //Extracts the argument from the input.
    void readArgument(string& line);

    //Extracts the fileName from the input.
    void readInputFileName(string& line);

    void readOutputFileName(string& line);

    //Throw exception if input is not entered correctly.
    void checkForBadInput(string& line);

    //Extracts the first word of input. Used for getting the command type. Passed by reference, changes the original.
    static string extractFirstWord(string& line);

    //Removes the additional starting blancos, if they exist.
    static void removeLeadingBlancos(string& line);

    //Throws an exception if unexpected characters are present.
    static void FindUnexpectedCharacters(string& line);

    //Resets params.
    void cleanParams(CommandParams& params);

    //All the extracted parameters are stored in the struct of type CommandParams.
    CommandParams params;

    //Has the object of the class used to determine the type of the command.
    CommandType commandType;

    //Pointer to the object of class Reader. Used for reading the lines.
    Reader* reader;

};
#endif
