#include "public/common.h"

#include "simpleParser.h"

using namespace std;

int main()
{
    cout << "Please Input an string of Numbers: ";
    string zsstr;
    cin >> zsstr;
    simpleParser zsParser;
    cout << "The answer is: " << zsParser.parseAndSum(zsstr) << endl;

    return 0;
}