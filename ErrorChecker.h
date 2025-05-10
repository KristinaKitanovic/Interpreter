#ifndef UNTITLED24_ERRORCHECKER_H
#define UNTITLED24_ERRORCHECKER_H
#include <exception>
#include <string>
#include <unordered_set>
using namespace std;

//Classes derived from exception.

//Exception when we want to create a file which already exists.
class FileAlreadyExistsError : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we enter an invalid command.
class InvalidCommandError : public exception {
public:
    InvalidCommandError(const string& commandName) : commandName(commandName) {}
    const char* what() const noexcept override;

private:
    string commandName;

    //Mutable allows changing in the const what function.
    mutable string message;
};

//Exception when we try to read from a file which does not exist.
class FileDoesNotExistError : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we try to set ready notifier to a string longer than 1 character.
class NotAChar : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we do not type the command in the right format.
class BadFormat : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we entered the option for comand that has no options.
class HasCommand : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we did not enter option for command that requires option.
class NoCommand : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we entered the argument for comand that has no arguments.
class HasArgument : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we did not enter argument for command that requires argument.
class NoArgument : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we entered the filename for comand that has no filename.
class HasFile : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we did not enter filename for command that requires filename.
class NoFile : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when we try to redirect output but command has no output.
class  HasRedirectedOutput : public exception {
public:
    const char* what() const noexcept override;
};

//Excepton when we enter both input file and argument.
class HasBothArgumentAndInputFile : public exception {
public:
    const char* what() const noexcept override;
};

class TooManyOptions : public exception {
public:
    const char* what() const noexcept override;
};

class TooManyOutputFiles : public exception {
public:
    const char* what() const noexcept override;
};

class TooManyInputFiles : public exception {
public:
    const char* what() const noexcept override;
};

class InputAfterFile : public exception {
public:
    const char* what() const noexcept override;
};

class TooManyArguments : public exception {
public:
    const char* what() const noexcept override;
};

class WrongNumberOfArguments : public exception {
public:
    const char* what() const noexcept override;
};

class BadOption : public exception {
public:
    const char* what() const noexcept override;
};

//Exception when input line has unexpected characters such as %, *, ? outside of quotes...
class UnexpectedCharacters : public exception {
public:
    UnexpectedCharacters(string line, unordered_set<int> v) : v(move(v)), line(move(line)) {}
    const char* what() const noexcept override;

private:
    string line;
    unordered_set<int> v;
};

//Class for catching errors thrown thoughout the program.
class ErrorChecker {
public:
    static void checkErrors(const exception& e);
};
#endif
