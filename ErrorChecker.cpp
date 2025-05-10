#include "ErrorChecker.h"
#include <iostream>

const char* FileAlreadyExistsError::what() const noexcept { return "Error: File Already Exists...\n"; }

const char* FileDoesNotExistError::what() const noexcept { return "Error: File Does Not Exist...\n"; }

const char* InvalidCommandError::what() const noexcept {
    message = "Error : Invalid Command : " + commandName + "\n";
    return message.c_str();
}

const char* NotAChar::what() const noexcept { return "Error : Ready Notifier must be a character...\n"; }

const char* BadFormat::what() const noexcept { return "Error : Bad Format...\n"; }

const char* HasCommand::what() const noexcept { return "Error : This command should not have an option...\n"; }

const char* NoCommand::what() const noexcept { return "Error : Option for this command is required...\n"; }

const char* HasArgument::what() const noexcept { return "Error : This command should not have an argument...\n"; }

const char* NoArgument::what() const noexcept { return "Error : Option for this argument is required...\n"; }

const char* HasFile::what() const noexcept { return "Error : This command should not have a file...\n"; }

const char* NoFile::what() const noexcept { return "Error : File for this command is required...\n"; }

const char* HasRedirectedOutput::what() const noexcept { return "Error : Trying to redirect output but this command has no output...\n"; }

const char* HasBothArgumentAndInputFile::what() const noexcept { return "Error : Cannot enter both argument and redirection of input file...\n"; }

const char* TooManyOptions::what() const noexcept { return "Error : You cannot enter more than one option...\n"; }

const char* TooManyInputFiles::what() const noexcept { return "Error : You cannot enter more than one input file...\n"; }

const char* TooManyOutputFiles::what() const noexcept { return "Error : You cannot enter more than one output file...\n"; }

const char* TooManyArguments::what() const noexcept
{
    return "Error : This command cannot have more than one argument...\n";
}

const char* InputAfterFile::what() const noexcept { return "Error : File redirection should be at the very end of command...\n"; }

const char* WrongNumberOfArguments::what() const noexcept { return "Error : Wrong number of arguments for this command...\n"; }

const char* BadOption::what() const noexcept { return "Error : Option you entered is not correct. It either does not exist or is in bad format...\n"; }

const char* UnexpectedCharacters::what() const noexcept {

    static string str = "";
    str = "Error : Unexpected characters...\n" + line + "\n";
    string str1 = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (v.find(i) != v.end()) str1 += "^";
        else
            str1 += " ";
    }
    str += str1;
    str += "\n";
    return str.c_str();
}

void ErrorChecker::checkErrors(const exception& e) {
    try {
        throw;
    }
    catch (const exception& e)
    {
        cout << e.what();
    }
}