#include "gtest/gtest.h"

#include "logAnalyzer2.h"

// Remember that namespaces are a good idea and good for your health.

// 用测试名来表征测试，而不是用注释“测试失败”
// TEST(TestCaseName, TestName)
// 测试类定义
class Analyze_WebThrows_SendEmail : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

  public:
};

// TEST_F(TestClassName, TestName)
TEST_F(Analyze_WebThrows_SendEmail, CheckEmail_returnTrue)
{
    // SetUp
    FakeWebService* pStubService = new FakeWebService();
    FakeEmailService* pMockEmailService = new FakeEmailService();
    LogAnalyzer2 log(pStubService, pMockEmailService);

    // Process
    string tooShortFileName = "abc.txt";
    log.Analyze(tooShortFileName);

    // Check
    string sExpectedBody = "fake exception";
    // for C Strings, use ASSERT_STREQ(s1, s2)
    ASSERT_EQ(sExpectedBody, pMockEmailService->Body);
}

// TEST_F(TestClassName, TestName)
TEST_F(Analyze_WebThrows_SendEmail, CheckEmailInfo_returnTrue)
{
}
