

#include "calculate.h"


float cal(int a, int b)
{
    float result;
    int sum = add_two(a,b) + sub(a,b) + mul(a,b);

    result = sum / 3;
    return result;
}
