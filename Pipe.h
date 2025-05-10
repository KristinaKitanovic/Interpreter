#ifndef PIPE_H
#define PIPE_H
#include "Parser.h"
#include "ParameterFormatter.h"
#include "Preparator.h"
#include "Executor.h"
#include "Reader.h"
#include "Writter.h"

class Executor;

class Pipe
{
public:
    friend class Interpreter;
    static Pipe* Instance();
    void process();
    static void execute(string& line);
    ~Pipe();


private:
    Pipe();
    static string extractCommand(string& line);
    static void cleanParams(CommandParams& params);
    static Parser parser;
    static ParameterFormatter parameterFormatter;
    static Preparator preparator;
    static Executor executor;
    Reader* reader;
};





#endif