#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Parser.h"
#include "Executor.h"
#include "Preparator.h"
#include "ErrorChecker.h"
#include "ParameterFormatter.h"
#include "Pipe.h"

class Preparator;
class Executor;
class Pipe;

//Interpreter is a class with the highest priority. It's Singleton, meaning only one instance of it is allowed.
class Interpreter {
public:

    //Triggers the process of reading commands from command line
    void perform();

    //Changes the ReadyNotifier
    void changeReadyNotifier(const string& argument);

    //Returns an Instance of class Interpreter
    static Interpreter* Instance();

private:
    Interpreter() = default;

    ~Interpreter() = default;

    //Char which signalizes that Interpreter is ready for the next command.
    char readyNotifier = '$';

    static Pipe pipe;
    static ErrorChecker errorChecker;

};


#endif
