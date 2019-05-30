#pragma once

using namespace std;

// 前向声明的类，不能使用其方法
// 由于LogAnalyzer2中包含该成员，而非指针，所以必须将IWebService声明在前面
// 如果用指针的话就可以任意顺序定义类
class IWebService;
class IEmailService;

// *****************************************************************************
// LogAnalyzer2 declaration
// *****************************************************************************
class LogAnalyzer2
{
public:
    LogAnalyzer2(IWebService* pIWebService, IEmailService* pIEmailService);
    ~LogAnalyzer2();
    // 公有成员
    void Analyze(string filename);

private:
    // 私有成员
    IWebService* m_pIWebService;
    IEmailService* m_pIEmailService;
    // 私有方法
};

// *****************************************************************************
// IWebService declaration
// 真实的类，此处只给出虚接口
// *****************************************************************************
class IWebService
{
public:
    IWebService();
    virtual ~IWebService();
    // 公有成员
    virtual void LogError(string message) = 0;

private:
    // 私有成员

    // 私有方法
};

// *****************************************************************************
// IEmailService declaration
// 真实的类，此处只给出虚接口
// *****************************************************************************
class IEmailService
{
public:
    IEmailService();
    ~IEmailService();
    // 公有成员
    virtual void SendEmail(string To, string Subject, string Body) = 0;

private:
    // 私有成员

    // 私有方法
};

// *****************************************************************************
// FakeWebService declaration
// MockClass 继承于真实类，重写父类的方法
// 此处父类无定义，所以子类全部为新建
// *****************************************************************************
class FakeWebService : public IWebService
{
public:
    FakeWebService();
    ~FakeWebService();
    // 公有成员
    virtual void LogError(string message);

private:
    // 私有成员

    // 私有方法
};

// *****************************************************************************
// FakeEmailService declaration
// MockClass 继承于真实类，重写父类的方法
// 此处父类无定义，所以子类全部为新建
// *****************************************************************************
class FakeEmailService : public IEmailService
{
public:
    FakeEmailService();
    ~FakeEmailService();
    // 公有成员
    string To;
    string Subject;
    string Body;
    virtual void SendEmail(string To, string Subject, string Body);

private:
    // 私有成员

    // 私有方法
};

// *****************************************************************************
// EmailInfo declaration
// 为了减少断言数量，将三个数据包裹成一个类
// *****************************************************************************
class EmailInfo
{
public:
    string Body;
    string To;
    string Subject;
};
