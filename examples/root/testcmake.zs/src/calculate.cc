

#include "calculate.h"
// #include "add/add.h"
#include "sub/sub-two.h"
#include "mul/mul-two.h"
// extern int mul(int a,int b);
// extern int sub(int a,int b);
// extern int add_two(int a,int b);
float cal(int a, int b)
{
    float result;
    int sum = add_two(a,b) + sub(a,b) + mul(a,b);

    result = sum / 3;
    return result;
}
