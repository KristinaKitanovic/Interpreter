
#ifndef READER_H
#define READER_H
#include <string>
#include <fstream>
#include "ErrorChecker.h"
using namespace std;

//class Reader, used to read a line. Abstract class. Base class.
class Reader {
public:
    //Constructor and Destructor.
    Reader(istream* input);

    virtual ~Reader() = default;

    //Gets next line from the source.
    virtual string getNextLine() = 0;

    //Checks whether we reached the end of reading.
    virtual bool endOfRead() = 0;
protected:
    //Pointer to an input stream, could point to different types of streams, such as cin or a file stream like ifstream.
    istream* input;
};

//Derived class. Derived from base class Reader. Used to read a line from input stream.
class InputStreamReader : public Reader {
public:
    //Constructor and destructor
    InputStreamReader();

    ~InputStreamReader() override = default;

    string getNextLine() override;

    bool endOfRead() override;

};

//Derived class. Derived from base class Reader. Used to read a line from a file.
class FileReader : public Reader {
public:

    //Retruns the only instance of FileReader.
    static FileReader* Instance(const string& fileName = "");

    ~FileReader() override;

    //Open new File.
    void openNewFile(const string& fileName);

    string getNextLine() override;

    bool endOfRead() override;

protected:
    //Explicit : Prevents implicit conversions.
    //Const : Cannot be changed in the constructor.
    //Reference : Avoids copying, saving time and memory.
    explicit FileReader(const string& filepath);
};
#endif
