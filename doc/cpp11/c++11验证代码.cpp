//原子类型实现
#include <atomic>
#include <iostream>
#include <list>
#include <thread>
#include <unistd.h>

#include <future>
using namespace std;



/******************************for的验证*****************************/
int g_adwData[3] = {1, 2, 3};
vector<int> g_vecData(g_adwData, g_adwData + 3);
extern "C" void test_c11for()
{
   for (int& i : g_adwData)   // C++11支持，VS2012之后支持
   {
       i *= 2;
   }
   for (auto& i : g_vecData)  // C++11支持，VS2012之后支持
   {
       i *= 2;
   }
   for (auto i : g_adwData)   // C++11支持，VS2012之后支持
   {
       cout << i << endl; // 输出：2 4 6
   }
   for (auto i : g_vecData)   // C++11支持，VS2012之后支持
   {
       cout << i << endl; // 输出：2 4 6
   }
}
/******************************long long类型的验证*****************************/
extern "C" void test_longlong()
{
    long long ll_min = LLONG_MIN;     //有符号long long 类型，头文件 climits 定义的long long 类型最小值  LLONG_MIN
    long long ll_max = LLONG_MAX;     //有符号long long 类型，头文件 climits 定义的long long 类型最大值  LLONG_MAX
    unsigned long long ull_max = ULLONG_MAX;  //无符号long long 类型，头文件 climits 定义的unsigned long long 的最大值ULLONG_MAX
    printf("sizeof(ll_min) %d,sizeof(ull_max) %d\n", sizeof(ll_min), sizeof(ll_max)); // 字节数 分别为 8、8
    printf("min of long long is %lld\n", LLONG_MIN); //-9223372036854775808
    printf("max of long long is %lld((0x%llx))\n", ll_max, ll_max); //9223372036854775807 0x7fffffffffffffff
    printf("max of long long is %llu(0x%llx)\n", ull_max, ull_max);//18446744073709551615   0xffffffffffffffff
}
 extern "C"  void test_longlongint()
 {
     long long int ll_min = LLONG_MIN;  //有符号long long 类型，头文件 climits 定义的long long 类型最小值  LLONG_MIN
     long long int ll_max = LLONG_MAX;  //有符号long long 类型，头文件 climits 定义的long long 类型最大值  LLONG_MAX
     unsigned long long int ull_max = ULLONG_MAX; //无符号long long 类型，头文件 climits 定义的unsigned long long 的最大值ULLONG_MAX
     printf("sizeof(ll_min) %d,sizeof(ull_max) %d\n", sizeof(ll_min), sizeof(ll_max)); // 字节数 分别为 8、8
     printf("min of long long is %lld\n", LLONG_MIN);  //-9223372036854775808
     printf("max of long long is %lld((0x%llx))\n", ll_max, ll_max);  //9223372036854775807 0x7fffffffffffffff
     printf("max of long long is %llu(0x%llx)\n", ull_max, ull_max); //18446744073709551615   0xffffffffffffffff
 }

extern "C"  void test_signedlonglongint()
{
    signed long long int ll_min = LLONG_MIN;  //有符号long long 类型，头文件 climits 定义的long long 类型最小值  LLONG_MIN
    signed long long int ll_max = LLONG_MAX;   //有符号long long 类型，头文件 climits 定义的long long 类型最大值  LLONG_MAX
    unsigned long long int ull_max = ULLONG_MAX; //无符号long long 类型，头文件 climits 定义的unsigned long long 的最大值ULLONG_MAX
    printf("sizeof(ll_min) %d,sizeof(ull_max) %d\n", sizeof(ll_min), sizeof(ll_max)); // 字节数 分别为 8、8
    printf("min of long long is %lld\n", ll_min);   //-9223372036854775808
    printf("max of long long is %lld((0x%llx))\n", ll_max, ll_max);   //9223372036854775807 0x7fffffffffffffff
    printf("max of long long is %llu(0x%llx)\n", ull_max, ull_max);   //18446744073709551615   0xffffffffffffffff
}

extern "C"  void test_initList()
{
    int a[]{ 2,4,6 };
    vector<int> b{ 1,3,5 };
    vector<int> c = { 1,3,5 };
    map<int, float> d = { {1,1.0f},
                          {2,2.0f},
                          {5,3.2f} };
}

/************************防止类型收窄************************/
extern "C"  void test_NoCut()
{
    const int x = 1024;
    const int y = 10;
    char z = 1;
    char a = x;                 //收窄，但可以通过编译
    char *a1 = new char(1024);  //收窄，但可以通过编译
#ifndef _WIN32
    char b = {x};               //数值收窄，【无法通过编译】  显示转换：char b = {(char)x};
#endif
    char b1 = {y};              //未收窄，可以通过编译
    short b2 = { z};              //类型收窄，【无法通过编译】
    unsigned char b3{255};        //未收窄，可以通过编译
    float c {7};                    //可以通过编译
#ifndef _WIN32
    int c1{2.0f};                   //收窄，【无法通过编译】
    float *c3 = new float{1e48};    //收窄，【无法通过编译】
#endif
}
/***************************静态断言****************************/

template <typename T, typename U>
void bit_copy(T &a, U &b)
{
    //static_assert(sizeof(a) == sizeof(b), "the parameters of bit_copy must have same width!");
                         //error C2338: the parameters of bit_copy must have same width!
    memcpy(&a, &b, sizeof(b));
}

extern "C"  void test_run_assertion()
{
    int a = 0x1234;
    double b = 0;
    bit_copy(a, b);
}
/***************************强类型枚举****************************/

enum struct Weight1 {General, Heavy, Light};
enum class Size1 {General, Little, Big};
enum class EnumChar : char{ X, Y, Z };
enum class EnumInt : long long int{ X, Y, Z = 0xFFFFFFFFF0 };
extern "C"  void test_Enum_Class1()
{
    Size1 s = Size1::General;
    Weight1 w = Weight1::General;
  //  Weight1 w1 = Light; // 编译失败，必须使用强类型名称
//    if (w == Size1::General){ } // 编译失败，必须使用Weight1中的General
 //   if(w > 0 ){} // 编译失败，不允许隐式转换为整型
    if((int)w > 0) {} // 编译成功，允许强制转换为整型
    if((int)s == (int)w){} // 编译成功，允许强制转换为整型
    cout << sizeof(EnumInt::Z) << " " << (long long int)EnumInt::Z << endl; // VS2015输出：8 4294967280
}

/***************************类成员初始化****************************/


class  c_init_2
 {
 public:
     c_init_2()
     {
         cout << "a:" << a <<"  "<< "b:" << b << endl;
     }
     c_init_2(int i_a, int i_b) :a(i_a), b(i_b)
     {
         cout << "a:" << a << "  "<< "b:" << b << endl;
     }
 private:
     int a = 1;
     int b = 2;
};

extern "C"  void  test_class_init()
{
    c_init_2 init_1;   //a:1 b:2
    c_init_2 init_2(5,6); //a:5 b:6
}

/***************************空指针的改进****************************/

extern "C"  void  test_nptr()
{
//#ifndef _WIN32
 //   nullptr += 1;           //报错
 //   int i = 4 + nullptr;   //报错
//#endif
    char *cp = nullptr;                       //隐式转换
    nullptr_t nptr = nullptr;

//    int n1 = nullptr;                       //报错
//    int n2 = reinterpret_cast<int> nullptr; //报错

    if (nptr);          //vs2015可以编译通过，但C++11标准要求报错。如果能通过，则说明编译器不够新
    if (0 == nptr);     //同上
    if(nptr == nullptr)
    {
        cout << "nullptr_t == nullptr" << endl;
    }
    int iA = 0;
    int * pA = &iA;
    if (nullptr != pA)
    {
        cout << "pA != nullptr" << endl;
    }

}


/***************************lambda函数****************************/

extern "C"  void test_lambda_base_1()
{
    int male = 6;
    int female = 3;
    [] {}; // 最简单的lambda函数
    auto sum_1 = [](int m, int f) {return m + f; };
    cout << "1.1 sum = " << sum_1(male, female) << endl; // 1.1 sum = 9
    cout << "1.2 sum = " << [](int m, int f) {return m + f; }(male, female) << endl; // 1.2 sum = 9
    auto sum_2 = [=]() {return male + female; };
    // auto sum_2_1 = [=]() {male += 1; return male + female; };
    cout << "1.3 sum = " << sum_2() << endl; // 1.3 sum = 9
    auto sum_3 = [&]() {male += 1; return male + female; };
    auto sum_3_1 = [&male, female] {male += 1; return male + female; };
    auto sum_3_2 = [&, female] {male += 1; return male + female; };
    cout << "1.4 sum = " << sum_3() << ", "; cout << "male = " << male << endl; // 1.4 sum = 10, male = 7
}

class sum
{
public:
    int operator()(int m, int f) { return m + f; }
};
void test_lambda_functor()
{
    int male = 6;
    int female = 3;
    sum sum;
    cout << "2.1 sum = " << sum(male, female) << endl; // 3.2 low tax = 1500
}

class tax
{
public:
    tax(float rate, int base):m_rate(rate),m_base(base){}
    float operator()(int money)
    {
        // auto high_lambda = [=]() {return (money - m_base) * m_rate; };
        // return high_lambda();  // 这样写也是可以的
        return (money - m_base) * m_rate;
    }
private:
    float m_rate;
    int m_base;
};
extern "C"  void test_lambda_spec()
{
    tax high(0.4,30000);
    tax low(0.3, 20000);
    cout << "3.1 high tax = " << high(37500) << endl; // 3.1 high tax = 3000
    cout << "3.2 low tax = " << low(25000) << endl; // 3.2 low tax = 1500
    float rate = 0.4;
    int base = 30000;
    auto high_lambda = [=](int money) {return (money - base) * rate; };
    rate = 0.3, base = 20000;
    auto low_lambda = [=](int money) {return (money - base) * rate; };
    cout << "3.3 high tax = " << high_lambda(37500) << endl; // 3.3 high tax = 3000
    cout << "3.4 low tax = " << low_lambda(25000) << endl; // 3.4 low tax = 1500
}

auto tax_calc(int base, float rate) // lambda函数作为返回值
{
    return [=](int money) {return (money - base) * rate; };
}
extern "C"  void test_lambda_app()
{
    auto high_lambda = tax_calc(30000, 0.4);
    auto low_lambda = tax_calc(20000, 0.3);
    auto low = low_lambda; // 通过赋值传递
    // call(low_lambda); // 编译不过，因为C++11的lambda函数没有专门的类型，而auto又不能作为形参类型
    cout << "4.1 high tax = " << high_lambda(37500) << endl; // 4.1 high tax = 3000
    cout << "4.2 low tax = " << low_lambda(25000) << endl; // 4.2 low tax = 1500
}

int g_val = 8;
auto L = [=] {return 1; }; // VS 2015编译通过，全局匿名函数的捕捉列表非空
extern "C"  void test_lambda_other()
{
    // auto F = [g_val] {return g_val; }; // VS 2015编译不过，提示不允许捕获非自动变量
    auto F = [=](int x) ->int {return g_val + x; }; // 但是VS 2015这样却是可以的
    cout << "5.1 F() = " << F(10) << endl; // 5.1 F() = 18
    auto L1 = [](int x) {return 8 + x; };
    typedef int (*pF)(int);
    pF pfunc = L1;
    // L1 = pfunc; // 编译不通过
    cout << "5.2 pfunc() = " << pfunc(4) << endl; // 5.2 pfunc() = 12
    int val = 10;
    auto by_val_lambda = [=] {return val; };
    auto by_ref_lambda = [&] {return val; };
    val++;
    cout << "5.3 by_val_lambda() = " << by_val_lambda() << endl; // 5.3 by_val_lambda() = 10
    cout << "5.3 by_ref_lambda() = " << by_ref_lambda() << endl; // 5.3 by_ref_lambda() = 11
}

/****************************override/final描述符***************************/

class BaseClass1
{
public:
    BaseClass1(){}
    ~BaseClass1(){}
public:
    virtual void func(int param) { cout << "BaseClass1::func. param = "  << param <<endl; }
    virtual void func2() const { cout<< "BaseClass1::func2."<<endl;}
    };

class DeriveClass1 : public BaseClass1
{
public:
    DeriveClass1(){}
    ~DeriveClass1(){}
public:
//#ifndef _WIN32
    //error C3668: 'DeriveClass::func' : method with override specifier 'override' did not override any base class methods
//    virtual void func(float param) override { cout << "DeriveClass1::func. param = "  << param <<endl; }

    //error C3668: 'DeriveClass::func2' : method with override specifier 'override' did not override any base class methods
//    virtual void func2() override { cout<< "DeriveClass1::func2."<<endl;}
//#endif
};

class BaseClass
{
public:
    BaseClass(){}
    ~BaseClass(){}
public:
    virtual void func(int param) final { cout << "BaseClass::func. param = "  << param <<endl; }
};

class DeriveClass : public BaseClass
{
public:
    DeriveClass(){}
    ~DeriveClass(){}
public:
#ifndef _WIN32
    //error C3248: 'BaseClass::func': function declared as 'final' cannot be overridden by 'DeriveClass::func'
   // virtual void func(int param) override { cout << "DeriveClass::func. param = "  << param <<endl; }
#endif
};

/************************并行计算**********************************************/
string taskFunc1()
{
    cout << "This is a task 1!" << endl;
    cout << "This is a task 1!" << endl;
    cout << "This is a task 1!" << endl;
    cout << "This is a task 1!" << endl;
    string str = "This returns task1.";
    return str;
}
string taskFunc2()
{
    cout << "This is a task 2!" << endl;
    cout << "This is a task 2!" << endl;
    cout << "This is a task 2!" << endl;
    cout << "This is a task 2!" << endl;
    string str = " This returns task2.";
    return str;
}
extern "C"  int test_multi_tasks()
{
    auto fut1 = async(taskFunc1);
    auto fut2 = async(taskFunc2);
    cout << (fut1.get() + fut2.get()) << endl;
    cout << "This is main program" << endl;
    return 0;
}

/*****************************兼容C99****************************************/
extern "C"   void test_pre_defined_macro()
{
     cout << "Standard Clib: " << __STDC_HOSTED__ << endl; // VS2015 undefined
#ifndef _WIN32
     cout << "Standard C: " << __STDC__ << endl; // VS2015 undefined
//     cout << "C Standard version" << __STDC_VERSION__ << endl; // VS2015 undefined
//     cout << "ISO/IEC: " << __STDC_ISO_10646 << endl; // VS2015 undefined
#endif
}

 class CTestClass
{
public:
    CTestClass() :m_name(__func__) {}
    const char* m_name;
};
extern "C"  void test_func()
{
    // 注：__func__定义为const char __func__[10] = "test_func"
    cout << __func__ << endl; // test_func
    // 注：__FUNCTION__定义为(const char[10])"test_func"
    cout << __FUNCTION__ << endl; // test_func
    CTestClass tc;
    cout << tc.m_name << endl; // CTestClass
}

 #pragma once // 指示编译器该头文件只被编译一次，效果与 #ifndef _HEAD  #define _HEAD  #endif一样
//#else
_Pragma("once"); // 效果与#pragma once一样




 #define LOG(...) printf(__VA_ARGS__) // __VA_ARGS__就是“...”所代表的字符串
extern "C"  void test_variable_args()
{
    printf("%s\n", "2017.2.20"); // 2017.2.20
    LOG("%s\n", "2017.2.20"); // 2017.2.20
}



/*****************************原子类型与原子操作****************************************/

atomic_llong total{ 0 }; //原子数据类型atomic_llong
void func(int)
{
    for (long long i = 0; i < 100000000ll; ++i)
    {
         total += i;  //原子类型不需要用pv操作
    }
}
extern "C"   void test_atomic_type1()
{
    thread t1(func, 0);
    thread t2(func, 0);
    t1.join();
    t2.join();
    func(0);
    func(0);
    cout << total << endl; //9999999900000000
    int i = 1000000000ll;
    while (i>0) {i--;};
    return ;
}
//原子类型使用规则
//atomic_llong total{ 0 }; //原子数据类型atomic_llong
//static long long total{ 0 };
std::atomic<float> af{1.3f};
#if 0
std::atomic<float> af1{af};  //原子类型不能拷贝构造，移动构造，以及=赋值等操作。
std::atomic<float> af2 = af;
//error: use of deleted function 'std::atomic<_Tp>::atomic(const std::atomic<_Tp>&) [with _Tp = float]'
#endif
float ad1 = af;   // ad1 = af.load();
float ad2{ af };  //原子类型可以赋值给其他非原子类型变量。因为atomic模板定义了由atomic<T>转换为T的类型转换函数。
//用原子类型实现“自旋”的一个例子
std::atomic_flag my_lock = ATOMIC_FLAG_INIT;
void f(int n)
{
    while (my_lock.test_and_set(std::memory_order_acquire))   //尝试获得锁
         cout << "Waiting from thread " << n << endl;       //自旋
    cout << "Thread " << n << " starts working " << endl;
}
void g(int n)
{
    cout << "Thread " << n << " is going to start. " << endl;
    my_lock.clear();
    cout << "Thread " << n << " starts working " << endl;
}
extern "C"   void test_atomic_type()
{
    my_lock.test_and_set();
    thread t1(f, 1);
    thread t2(g, 2);
    f(1);
    g(2);
    t1.join();
    sleep(10000);
    t2.join();
    //while (1) {};
   // return 0;
}


/*****************************移动语义****************************************/

class HasPtrMem
{
public:
    HasPtrMem() :p(new int(0))
    {
        ++n_cstr;
        printf("structure times:%d\n", n_cstr);
    }
    HasPtrMem(const HasPtrMem &h) :p(new int(*h.p))
    {
        ++n_cptr;
        printf("copy structure times:%d\n", n_cptr);
    }
    HasPtrMem(HasPtrMem &&h) :p(h.p) /*右值引用参数：可理解为临时变量的引用*/
    {
        h.p = nullptr;/*内存已被偷走，临时变量指针赋空*/
        ++n_mvtr;
        printf("move structure times:%d\n", n_mvtr);
    }
    ~HasPtrMem()
    {
        ++n_dstr;
        printf("destruct times:%d\n", n_dstr);
    }
private:
    static int n_cstr;/*构造次数*/
    static int n_dstr;/*析构次数*/
    static int n_cptr;/*拷贝构造次数*/
    static int n_mvtr;/*移动构造次数*/
    int *p;
};
int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_mvtr = 0;


HasPtrMem GetTemp()
{
    HasPtrMem h;
    return h;
}

extern "C"   void test_move_ptr()
{
    HasPtrMem temp = GetTemp();
}



/*****************************显式转换操作符****************************************/

template <typename T>
class Ptr
{
public:
    explicit Ptr(T* p) : m_p(p) {}
    explicit operator bool() const  // 注意这行的 explicit
    {
        if (nullptr != m_p)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    T * m_p;
};

extern "C"   void test_explicit_conversion_oprs()
{
    int ia = 0;
    Ptr<int> pa(&ia);
    if (pa)
    {
        cout << "valid pointer!" << endl; // 输出此行
    }
    else
    {
        cout << "invalid pointer!" << endl;
    }
#if 0
    cout << pa + 1 << endl;  // 编译错误
	// note:   cannot convert 'pa' (type 'Ptr<int>') to type 'std::ptrdiff_t {aka long int}'
#endif
    cout << (int)(bool)pa + 1<< endl;  // 2
}




/*****************************统一初始化的语法和语义****************************************/

string a[] = { "foo", "bar"}; //正确：初始化数组变量
vector<string> v = { "foo", "bar" };//错误：初始化列表应用在了非聚合的向量上
void f(string a[]);
int b = 2; //“赋值风格”的初始化
int aa[] = { 2,3 }; //用初始化列表进行的赋值风格的初始化
#if 0
strA z(1,2); //“函数风格”的初始化
//error: 'strA' does not name a type
double c = ff(b); // “函数风格”的转换/赋值/构造操作
//error: 'ff' was not declared in this scope
#endif
int m(1); //变量的定义
int test(); //函数的声明


// C++11的解决方法是对于所有的初始化，均可使用“{}   初始化变量列表”

struct X {
    X(initializer_list<int> iv) {}
    X(char a) {}
};
X x1 = X{ 1,2 };
X x2 = { 1,2 }; // 此处的'='可有可无
X x3{ 1,2 };
X x4{ 1,2,3 };
//X x5(1,2,3);
X* p = new X{ 1,2 };

struct D : X {
    D(int x, int y) :X{ x,y } { /* … */ };
};
struct S {
    int a[3];
    // 对于旧有问题的解决方案
    S(int x, int y, int z) :a{ x,y,z} { /* … */ };
};

/*****************************数据对齐****************************************/


struct HowManyBytes {
  char a;
  short sh;
  int  b;
 };
struct ColorVector {
  double r;
  double g;
  double b;
  double a;
 };


extern "C"   void test_alignof()
{
    cout << "sizeof(char): " << sizeof(char) << endl;                  //1
    cout << "sizeof(int): " << sizeof(int) << endl;                    //4
    cout << "sizeof(HowManyBytes): " << sizeof(HowManyBytes) << endl;  //8
#if 0
    //offset 用于计算成员在结构体中的地址偏移值，vc6已经支持
    cout << "offset of char a: " << offsetof(HowManyBytes, a) << endl;     //0
    cout << "offset of char sh: " << offsetof(HowManyBytes, sh) << endl;   //2
    cout << "offset of char b: " << offsetof(HowManyBytes, b) << endl;     //4
    //error: 'offsetof' was not declared in this scope
#endif
//C++11标准定义了操作符alignof  –- 查看数据的对齐方式。
    cout << "alignof (HowManyBytes): " << alignof(HowManyBytes) << endl;   //4
    cout << "alignof (ColorVector): " << alignof(ColorVector) << endl;     //8


// alignof能够支持的类型：
//1.内置类型和完整的自定义类型；
//2.变量、引用和数组。

struct Completed {};

//对于内置类型和完整的自定义类型，可以使用alignof
cout << alignof(int) << endl               //4
     << alignof(Completed) << endl         //1
     << sizeof(struct Completed) << endl;  //1

int w;
long long b;
auto &c = b;
char d[1024];

//对于变量、引用和数组，C++11标准允许使用alignof，但是目前vs2015的编译器并不支持，gcc编辑器提供支持。
#ifndef _WIN32
  cout << alignof(w) << endl       //4
       << alignof(b) << endl       //8
       << alignof(c) << endl       //8,与b同
       << alignof(d) << endl;      //1,与元素要求相同
#endif

//void test_alignas()
//ColorVector 定义的是向量数据，通常计算机要支持许多向量指令，为了能够直接对向量数据进行操作，C++11新提供了修饰符alignas ，用于重新设定结构体的对齐方式。
struct alignas(32) ColorVector {   //alignas(32)将结构体对齐到32字节的地址边界上。
  double r;
  double g;
  double b;
  double a;
};

cout << "alignof (ColorVector): " << alignof(ColorVector) << endl;    //32
cout << "sizeof (ColorVector): " << sizeof(ColorVector) << endl;      //32

//C++11规定了基本对齐值。一般情况下等于平台上支持的最大标量类型数据的对齐值。
cout << alignof(long double) << endl;      //最大标量类型数据的对齐值，常常是long double = 8
#ifdef _WIN32
cout << alignof(std::max_align_t) << endl; //可以通过std::max_align_t来查看最大对齐值 = 8
//gcc error: 'max_align_t' is not a member of 'std'
//Fixed for 4.9.0. If somebody is interested in 4.8.x too, backporting the patch should not be a big deal.
#endif
}

struct alignas(alignof(double)*4) ColorVectorT {   //alignas既可以接受类型作为参数，也可以使用常量表达式
  double r;
  double g;
  double b;
  double a;
 };
template <typename T>
class FixedCapacityArray {
 public:
#ifdef _WIN32
  char alignas(T)data[1024] = { 0 }; //alignas修饰符表明这个数组必须按照模板参数T的对齐方式进行对齐
  //note: an attribute that appertains to a type-specifier is ignored
#endif
};

//FixedCapacityArray固定使用1024个字节的空间，但是由于模板的存在，可以实例化为多种类型版本的数组。
extern "C"   void test_alignof_template()
{
//实例一
  FixedCapacityArray<char> arrCh;
  cout << "alignof (char): " << alignof(char) << endl;                        //1
  cout << "alignof (data): " << alignof(FixedCapacityArray<char>) << endl;    //1

//实例二
 FixedCapacityArray<ColorVectorT> arrCV;
 cout << "alignof (ColorVectorT): " << alignof(ColorVectorT) << endl;               //32
 cout << "alignof (data): " << alignof(FixedCapacityArray<ColorVectorT>) << endl;  //32

}

//需要注意的是，alignas不能够用于修饰函数。
#ifndef _WIN32
alignas(double) void func_aligned();  //报错 // gcc没有报错
#endif



/*****************************函数的默认模板参数****************************************/
//复习一下
template <typename T>
void TempFun(T a)
{
    cout << a << endl;
}
extern "C"   void test_template_old()
{
    TempFun(1);    //实例化为TempFun<const int >(1) )
    TempFun("1");  //实例化为TempFun<const char* >("1") )
}
//2、c++98不支持函数模板的默认模板参数，而C++11支持
void DefParm(int m = 3) {}     //c++98编译通过，C++11编译通过
template <typename t = int>
class DefClass {};              //c++98编译通过，C++11编译通过
template <typename t = int>
void DefTempParam() {};         //c++98编译失败，C++11编译通过

//3、无须 “从右往左”的规则进行指定。
template <typename T1,typename T2 = int> class DefClass1;
//template <typename T1 = int, typename T2> class DefClass2;  //无法编译通过
template <typename T, int i=0> class DefClass3;
//template <int i = 0 , typename T> class DefClass4;          //无法编译通过
template <typename T1 = int, typename T2>  void DefFunc1(T1 a, T2 b);
template <int i = 0, typename T>  void DefFunc2(T a);

//4、如果能够从函数实参中推导出类型，那么默认模板参数就不会被使用，反之，就会被使用。
template <class T, class U = double>
void f(T t = 0, U u = 0) {};

extern "C"   void test_template_new()
{
    f(1, 'c');     //f<int,char>(1, 'c')
    f(1);          //f<int, doubule>(1, 0),使用了默认模板参数double
    //f();         //错误 error: no matching function for call to 'f()'
    f<int>();      //f<int, doubule>(0, 0)，使用了默认模板参数double
    f<int, char>(); //f<int, char>(0, 0)
}



/*****************************模板的右双括号****************************************/

template <int i>
class Xright {};
template <class T>
class Yright {};
extern "C"   void test_template_right()
{
    Yright< Xright<1> > x1; // c++98 c++11 都编译成功。
    Yright<Xright<2>> x2;  // c++98 编译失败, 编译器会把 >> 优先解析为右移符号。 c++11编译成功，可智能地匹配模板括号。
    Xright<(1 >> 5)> x3; // c++98 编译成功。c++11 编译失败，编译器优先把双尖括号的第一个 > 与X之后的 < 进行了配对。
}
//如示例第3行所示，c++11 智能匹配模板括号的做法与c++98是不兼容的。 修改成 X<(1 >> 5)> x3,则c++11可编译通过。




/*****************************模板的别名****************************************/

typedef int myint;
typedef std::vector<std::string> strvec;
typedef unsigned int UINT;

//3、在c++11中定义的别名（新模式）
using uint = unsigned int;
using sint = int;

//4、在c++11定义模板的别名（新增）
template<typename T> using MapString = std::map<T, char*>;
MapString<int> numberedString;

//5、总结：using 关键字，c++11进行了扩展，包括了typedef的部分，而模板的别名的定义 typedef无法达到using的效果

/********************************auto类型推导*****************/
double foo() { return 0; }
struct T_TEST
{
    int i;
};
extern "C"   void test_auto_base()
{
    auto x = 1;
    auto d = foo();
    struct T_TEST str1 = {0};
    auto str2 = str1;


    cout << "x type: " << typeid(x).name() << endl;   // x type: int
    cout << "d type: " << typeid(d).name() << endl;   // d type: double
    cout << "str2 type: " << typeid(str2).name() << endl; // str2 type: struct T_TEST
    cout << endl;

}
extern "C"   void test_auto_complex()
{
    list<int> vi;
    vi.push_back(1);
    //for (list<int>::iterator i = vi.begin(); i != vi.end(); i++)
    for (auto i = vi.begin(); i != vi.end(); i++)   //注意看，代码变短了
    {
        cout << "i type: " << typeid(i).name() << endl; //i type: class std::_List_iterator<class std::_List_val<struct std::_List_simple_types<int> > >
        cout << *i << endl;                             // 1
    }
    cout << endl;

    float radius = 1.7f;
    double pi = 3.1415927f;
    auto circumference = 2 * pi * radius; // 注意看，auto类型 推导为提升后的类型
    cout << "circumference type: " << typeid(circumference).name() << endl;   // circumference type: double
    cout << endl;


    auto l = strlen("hello world!\n");               // 这里推导为 unsigned int。对于程序员来说，交给auto就可以了。
    cout << "l type: " << typeid(l).name() << endl;  // l type: unsigned int
    cout << endl;

    {
        int x = 1;
        auto y = &x;
        cout << "y type: " << typeid(y).name() << endl;     // y type: int *
        auto & r = x;
        r = 2;
        cout << "r type: " << typeid(r).name() << endl;    // r type: int
        cout << "x value: " << x << endl;                  // x value: 2     // x数值真得被修改了
    }
    cout << endl;

}

