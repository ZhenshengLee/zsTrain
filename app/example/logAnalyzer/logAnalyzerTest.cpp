#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "logAnalyzer.h"
#include "mock/mockLogAnalyzer.h"

// Remember that namespaces are a good idea and good for your health.
using ::testing::AtLeast;
using ::testing::HasSubstr;
using ::testing::Return;

// 用测试名来表征测试，而不是用注释“测试失败”
// TEST(TestCaseName, TestName)
// 测试类定义
class IsValidLogFileName : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    // virtual void TearDown()
    // {
    // }
public:

};

// TEST_F(TestClassName, TestName)
TEST_F(IsValidLogFileName, BadExtension_returnFalse)
{
    FileExtMgr fileExtMgr;
    LogAnalyzer m_Analyzer(&fileExtMgr);
    ASSERT_FALSE(m_Analyzer.IsValidLogFileName("filewithbadextension.foo"));
}

TEST_F(IsValidLogFileName, GoodExtensionLowerCase_returnTrue)
{
    FileExtMgr fileExtMgr;
    LogAnalyzer m_Analyzer(&fileExtMgr);
    ASSERT_TRUE(m_Analyzer.IsValidLogFileName("filewithgoodextension.slf"));
}
TEST_F(IsValidLogFileName, GoodExtensionUpperCase_returnTrue)
{
    FileExtMgr fileExtMgr;
    LogAnalyzer m_Analyzer(&fileExtMgr);
    ASSERT_TRUE(m_Analyzer.IsValidLogFileName("filewithgoodextension.SLF"));
}

// 使用新的matcher时注意添加命名空间
// Google Mock requires expectations to be set before the mock functions are called
// otherwise the behavior is undefined
TEST(zsIsValidLogFileName, BadExtension_returnFalse)
{
    // 初始化
    MockFileExtMgr fileExtMgr;
    LogAnalyzer m_Analyzer(&fileExtMgr);

    // 确定期待mock-class发生的行为
    EXPECT_CALL(fileExtMgr, IsValid(HasSubstr("extension.SLF")))
        .Times(AtLeast(1))
        .WillOnce(Return(true));
    EXPECT_TRUE(m_Analyzer.IsValidLogFileName("filewithgoodextension.SLF"));
}
