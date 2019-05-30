#include "public/common.h"

#include "example/LogAnalyzer2.h"

// *****************************************************************************
// LogAnalyzer2 Implementation
// *****************************************************************************
using namespace std;

LogAnalyzer2::LogAnalyzer2(IWebService* pIWebService, IEmailService* pIEmailService)
{
    m_pIWebService = pIWebService;
    m_pIEmailService = pIEmailService;
}

LogAnalyzer2::~LogAnalyzer2()
{
    m_pIWebService = NULL;
    m_pIEmailService = NULL;
}

void LogAnalyzer2::Analyze(string filename)
{
    if(filename.length() < 8)
    {
        try
        {
            m_pIWebService -> LogError("Filename too short:" + filename);
        }
        // ...能够捕捉任何异常
        // 此处捕获一个const char*的异常
        catch(const char* msg)
        {
            m_pIEmailService -> SendEmail("someone@somewhere.com", "can not log", msg);
        }
    }
}

// *****************************************************************************
// IWebService Implementation
// *****************************************************************************
IWebService::IWebService() {}

IWebService::~IWebService() {}

// *****************************************************************************
// IEmailService Implementation
// *****************************************************************************
IEmailService::IEmailService() {}

IEmailService::~IEmailService() {}

// *****************************************************************************
// FakeWebService Implementation
// *****************************************************************************
FakeWebService::FakeWebService() {}

FakeWebService::~FakeWebService() {}

void FakeWebService::LogError(string message)
{
    throw "fake exception";
}

// *****************************************************************************
// FakeEmailService Implementation
// *****************************************************************************
FakeEmailService::FakeEmailService() {}

FakeEmailService::~FakeEmailService() {}

void FakeEmailService::SendEmail(string to, string subject, string body)
{
    To = to;
    Subject = subject;
    Body = body;
}
