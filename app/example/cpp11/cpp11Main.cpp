// #include "public/common.h"

#include <stdio.h>
#include <iostream>
#include <list>
#include <thread>

#include "example/cpp11.h"

using namespace std;

void user_test()
{
    cout << "hello world!" << endl;
    cout << __cplusplus << endl;
}

void test_longlong()
{
    cout << "in amd64 platform" << endl;
    cout << "the size of int " << sizeof(int) << endl;
    cout << "the size of long " << sizeof(long) << endl;
    cout << "the size of longlong " << sizeof(long long) << endl;
    long long x3 = LLONG_MIN;
    printf("x3: %lld, x3:%#llx\n", x3, x3);
    char x4 = -127;
    printf("x4: %xc\n", x4);
    // 正数是原型，负数是补码
    //
}

struct T1
{
    int i;
};
struct U1
{
    long long lo;
};

void bit_copy(T1& a, U1& b)
{
    // static_assert(sizeof(a) == sizeof(b), "if false show this");
    memcpy(&a, &b, sizeof(b));
}

// const int GetConst()
constexpr int GetConst()
{
    return 1;
}

void Constless(int cond)
{
    int arr[GetConst()] = { 0 };
    enum
    {
        e1 = GetConst(),
        e2
    };

    switch (cond)
    {
        case GetConst():
            printf("you hit the point!\n");
            break;

        default:
            break;
    }
}

double foo()
{
    return 0;
}

struct T_TEST
{
    int i;
};

void test_auto()
{
    auto x = 1;
    auto d = foo();
    struct T_TEST str1 = { 0 };
    auto str2 = str1;
    auto c = 'a';

    cout << "x type:" << typeid(x).name() << endl;
    cout << "d type:" << typeid(d).name() << endl;
    cout << "str2 type:" << typeid(str2).name() << endl;
    cout << "char type:" << typeid(c).name() << endl;
}

void test_auto1()
{
    int x = 0;
    const long y = 100;
    int& z = x;
    auto a1 = ++x;
    auto& a2 = x;
    auto a3 = z;
    auto a4 = y * y;
    auto& a5 = y;
    const auto a6 = x + x;
    auto* a7 = &y;

    cout << "x type:" << typeid(x).name() << endl;
    cout << "y type:" << typeid(y).name() << endl;
    cout << "z type:" << typeid(z).name() << endl;
    cout << "a1 type:" << typeid(a1).name() << endl;
    cout << "a2 type:" << typeid(a2).name() << endl;
    cout << "a3 type:" << typeid(a3).name() << endl;
    cout << "a4 type:" << typeid(a4).name() << endl;
    cout << "a5 type:" << typeid(a5).name() << endl;
    cout << "a6 type:" << typeid(a6).name() << endl;
    cout << "a7 type:" << typeid(a7).name() << endl;
}

void test_for()
{
    double pi = 3.1415926f;
    list<float> rs = { 1.5f, 1.6f, 1.7f };
    for (auto& i : rs)
    {
        i = 2 * pi * i;
    }
    for (auto c : rs)
    {
        cout << c << endl;
    }
}

namespace S
{
enum Size
{
    Normal,
    Little,
    Big
};
}
namespace W
{
enum Weight
{
    Normal,
    Little,
    Big
};
}
namespace nn
{
enum Weight
{
    Normal = 2,
    Little,
    Big
};
}
void testEnum1()
{
    cout << "S::Normal=" << S::Normal << endl;
    cout << "S::Normal=" << S::Normal << endl;
    cout << "S::Normal=" << S::Normal << endl;
    S::Size s = S::Normal;
    W::Weight w = W::Normal;
    if (s == w)
    {
        cout << "s == w, it's strange!" << endl;
    }
}

enum class Weight
{
    General,
    Heavy,
    Light
};
enum class Size
{
    General,
    Little,
    Big
};
enum class EnumChar : char
{
    X,
    Y,
    Z
};
enum class Enumlong : long long
{
    X,
    Y,
    Z
};
void testEnum2()
{
    Weight w = Weight::General;
    EnumChar ec = EnumChar::X;
    Enumlong el = Enumlong::X;
    cout << "Weight size=" << sizeof(w) << endl;
    cout << "EnumChar size=" << sizeof(ec) << endl;
    cout << "Enumlong size=" << sizeof(el) << endl;
}

void test_nullptr()
{
    nullptr_t nptr = nullptr;
    if (nptr == nullptr)
    {
        cout << "nullptr == nullptr" << endl;
    }
    int iA = 0;
    int* pA = &iA;
    if (nullptr != pA)
    {
        cout << "pA != nullptr" << endl;
    }
}

struct HowManyBytes
{
    char a;
    short sh;
    int b;
};
void test_alignment()
{
    cout << "sizeof(HowManyBytes):" << sizeof(HowManyBytes) << endl;
    cout << "offset of char a:" << offsetof(HowManyBytes, a) << endl;
    cout << "offset of char sh:" << offsetof(HowManyBytes, sh) << endl;
    cout << "offset of char b:" << offsetof(HowManyBytes, b) << endl;
}

struct alignas(32) ColorVector
{
    double r;
    double g;
    double b;
    double a;
    double c;
};
void test_alignment2()
{
    cout << "alignof(ColorVector):" << alignof(ColorVector) << endl;
    cout << "sizeof(ColorVector):" << sizeof(ColorVector) << endl;
}

void hello()
{
    cout << "hello concurrent World!\n";
}

int main()
{
    // 主调用程序代码
    // 64位整型支持
    // test_longlong();

    // 静态断言
    // T1 a;
    // U1 b;
    // bit_copy(a, b);

    // 常量表达式
    // Constless(1);

    // auto类型推导
    // test_auto();
    // test_auto1();

    // for循环
    // test_for();

    // 强类型枚举
    // testEnum1();
    // testEnum2();

    // 强类型空指针
    // test_nullptr();

    // 字节对齐
    // test_alignment();
    // test_alignment2();

    // 右值引用

    // 并发编程
    thread t(hello);
    t.join();
    return 0;
}
