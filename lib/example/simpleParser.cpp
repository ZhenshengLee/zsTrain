#include "public/common.h"

#include "example/simpleParser.h"

using namespace std;

simpleParser::simpleParser() {}

simpleParser::~simpleParser() {}

int simpleParser::parseAndSum(string numbers)
{
    if (numbers.length() == 0)
    {
        cout << "Numbers length is 0" << endl;
        return 0;
    }
    if (numbers.find(',') == string::npos)
    {
        cout << "Ready to atoi" << endl;
        return atoi(numbers.c_str());
    }
    else
    {
        cout << "Else" << endl;
        // 抛出异常
        throw runtime_error("Data must be numbers");
    }
}
