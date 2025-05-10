#ifndef WRITTER_H
#define WRITTER_H
#include <string>
using namespace std;

class Writter {
public:
    static void write(string& outputFileName, const string& content);

private:
    static void appendOutput(string& outputFileName, const string& content);
    static void overwriteOutput(string& outputFileName, const string& content);
};

#endif
