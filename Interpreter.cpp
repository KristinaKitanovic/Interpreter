#include "Interpreter.h"
#include <iostream>

using namespace std;

//Definition of Pipe. Static member.
Pipe Interpreter::pipe;

//Definition of ErrorChecker. Static member.
ErrorChecker Interpreter::errorChecker;

//Singleton. Returns the only instance of class Interpreter. Allocated on the stack. Lifespan is the duration of the program.
//It automatically deletes itself once the program finishes.
Interpreter* Interpreter::Instance() {
    //Static keyword makes sure that instance is initialized only once.
    static Interpreter instance;
    return &instance;
}

//Changes the ReadyNotifier
void Interpreter::changeReadyNotifier(const string& argument) {

    if (argument.length() != 1) throw NotAChar();
    readyNotifier = argument[0];
}

//Triggers reading commands and executes them
void Interpreter::perform()
{
    while (true)
    {
        try {
            //Signalize (Ready for command input)
            cout << readyNotifier << " ";

            pipe.process();
        }
        catch (const exception& e)
        {
            //Catch Exceptions.
            errorChecker.checkErrors(e);
        }
        catch (...)
        {
            cout << "Unhandled exception...";
        }

    }
}



