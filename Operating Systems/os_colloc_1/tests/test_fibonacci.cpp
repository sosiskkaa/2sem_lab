#include <gtest/gtest.h>
#include "fibonacci.h"

using namespace std;

TEST(FibonacciTest, GenerateFirstN_ValidInput)
{
    auto result = FibonacciGenerator::generateFirstN(1);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
    
    result = FibonacciGenerator::generateFirstN(2);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    
    result = FibonacciGenerator::generateFirstN(5);
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 1);
    EXPECT_EQ(result[3], 2);
    EXPECT_EQ(result[4], 3);
}

TEST(FibonacciTest, GenerateFirstN_EdgeCases)
{
    EXPECT_TRUE(FibonacciGenerator::canSafelyGenerate(93));
    EXPECT_FALSE(FibonacciGenerator::canSafelyGenerate(94));
    
    EXPECT_NO_THROW(FibonacciGenerator::generateFirstN(93));
}

TEST(FibonacciTest, GenerateFirstN_InvalidInput)
{
    EXPECT_THROW(FibonacciGenerator::generateFirstN(0), invalid_argument);
    EXPECT_THROW(FibonacciGenerator::generateFirstN(100), overflow_error);
}

TEST(FibonacciTest, GenerateFirstN_LargeSequence)
{
    auto result = FibonacciGenerator::generateFirstN(10);
    vector<unsigned long long> expected = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    EXPECT_EQ(result, expected);
}

TEST(FibonacciTest, CanSafelyGenerate)
{
    EXPECT_TRUE(FibonacciGenerator::canSafelyGenerate(1));
    EXPECT_TRUE(FibonacciGenerator::canSafelyGenerate(50));
    EXPECT_TRUE(FibonacciGenerator::canSafelyGenerate(93));
    EXPECT_FALSE(FibonacciGenerator::canSafelyGenerate(94));
    EXPECT_FALSE(FibonacciGenerator::canSafelyGenerate(100));
    EXPECT_FALSE(FibonacciGenerator::canSafelyGenerate(0));
}