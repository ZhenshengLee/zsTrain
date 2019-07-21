#include "zst/common.h"

#include "zstinternal/tddtest/tddtest.h"

using namespace std;

int main()
{
    tddTest zsTddTest;
    int i = zsTddTest.expr("1+2");
    cout << "The Answer is: " << i << endl;

    return 0;
}