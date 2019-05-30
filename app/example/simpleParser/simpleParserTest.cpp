#include <gtest/gtest.h>

#include "example/simpleParser.h"

TEST(simpleParser, simpleNumbers)
{
    simpleParser zsParser;
    int expected = 12345;
    int actual = zsParser.parseAndSum("12345");
    ASSERT_EQ(expected, actual);
}