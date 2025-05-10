#include "Reader.h"
#include <iostream>
using namespace std;


//Assigns the passed istream* input to the class member variable input.
Reader::Reader(istream* input)
{
    this->input = input;
}

//Calls the constructor for Reader and passes CIN as the source for reading.
InputStreamReader::InputStreamReader() : Reader(&cin) {}

//Loads the line from input stream and stores it into a variable. Returns the read line.
string InputStreamReader::getNextLine() {
    string line;
    //Clear after reading EOF.
    if (input->eof() || input->fail()) {
        input->clear();
    }
    getline(*input, line);
    return line;
}

//EOF in InputStream will be Ctrl + Z
bool InputStreamReader::endOfRead() { return input->eof(); }

//Calls constructor for class Reader and passes the file as the source for reading.
FileReader::FileReader(const string& filepath) : Reader(new ifstream(filepath)) {
    if (!static_cast<ifstream*>(input)->is_open())
    {
        throw FileDoesNotExistError();
    }
}

//Closes the file and deletes the pointer to the file.
FileReader::~FileReader() {
    //Explicitly ensuring that input pointer is of type ifstream and not istream.
    ifstream* fileStream = static_cast<ifstream*>(input);
    if (fileStream) fileStream->close();
    delete input;
}

FileReader* FileReader::Instance(const string& fileName) {

    //If FileReader does not exist call the constructor.
    static FileReader instance(fileName);

    //Change the file you are reading from. Open new file with the new passed name.
    if (!fileName.empty()) {
        instance.openNewFile(fileName);
    }
    return &instance;
}

void FileReader::openNewFile(const string& fileName) {
    ifstream* fileStream = static_cast<ifstream*>(input);

    //Close the previous file.
    fileStream->close();

    //Open a new file.
    fileStream->open(fileName);

    //If it cannot be opened throw an exception.
    if (!fileStream->is_open())
    {
        throw FileDoesNotExistError();
    }
}

//Gets next line from the file.
string FileReader::getNextLine() {
    string line;
    getline(*input, line);
    return line;
}

//Return true if we got to the EOF.
bool FileReader::endOfRead() {
    return input->eof();
}

