#include "Pipe.h"

using namespace std;

Parser Pipe::parser;
ParameterFormatter Pipe::parameterFormatter;
Preparator Pipe::preparator;
Executor Pipe::executor;

Pipe::Pipe() {
    reader = new InputStreamReader();
}


Pipe::~Pipe()
{
    delete reader;
}

Pipe* Pipe::Instance() {
    static Pipe pipe;
    return &pipe;
}

void Pipe::cleanParams(CommandParams& params) {
    params.commandName.clear();
    params.arguments.clear();
    params.inputFileName.clear();
    params.outputFileName.clear();
}

string Pipe::extractCommand(string& line)
{
    int positionOfFirstLine = line.find('|');
    if (positionOfFirstLine == std::string::npos)
    {
        string command = line;
        line = "";
        return command;
    }
    string command = line.substr(0, positionOfFirstLine);
    line = line.substr(positionOfFirstLine + 1);
    return command;
}

void Pipe::execute(string& line)
{
    string result = "";
    CommandParams params;

    while (!line.empty()) {

        string com = extractCommand(line);
        //Load all the parameters from the input and store them in params.

        params = parser.parse(com, result);

        //Reformat parameters.
        parameterFormatter.reformatParameters(params);

        //Prepare the argument and make a command.
        Command* command = preparator.prepareAndFormCommand(params);

        //Execute.
        result = executor.executeCommand(command);
    }
    Writter::write(params.outputFileName, result);
}

void Pipe::process()
{

    string line = reader->getNextLine();
    Parser::TrimTo512(line);
    execute(line);



}