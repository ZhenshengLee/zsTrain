#include <gtest/gtest.h>

#include "helloWorld.h"

// testFixture: 使用一个对象进行组织，以便于多个测试项共用资源
// 测试类定义
class helloWorldTestFix : public ::testing::Test {
 protected:
   virtual void SetUp() {}

   // virtual void TearDown() {}

};

// TEST_F(TestClassName, TestName)
TEST_F(helloWorldTestFix, integer)
{
    zs zs_circle(1);
    ASSERT_EQ(9.8596, zs_circle.getArea());
}
