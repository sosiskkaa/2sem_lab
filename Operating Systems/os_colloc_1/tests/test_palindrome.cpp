#include <gtest/gtest.h>
#include "palindrome.h"

using namespace std;

TEST(PalindromeTest, IsPalindrome_Number)
{
    EXPECT_TRUE(PalindromeChecker::isPalindrome(0));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(5));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(121));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(1221));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(12321));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(1234321));
    
    EXPECT_FALSE(PalindromeChecker::isPalindrome(123));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(1234));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(10));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(100));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(123456));
}

TEST(PalindromeTest, IsPalindrome_SingleDigit)
{
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_TRUE(PalindromeChecker::isPalindrome(i));
    }
}

TEST(PalindromeTest, IsPalindrome_String)
{
    EXPECT_TRUE(PalindromeChecker::isPalindrome(""));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("a"));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("racecar"));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("madam"));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("aa"));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("aba"));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("abba"));
    EXPECT_TRUE(PalindromeChecker::isPalindrome("abcba"));
    
    EXPECT_FALSE(PalindromeChecker::isPalindrome("hello"));
    EXPECT_FALSE(PalindromeChecker::isPalindrome("world"));
    EXPECT_FALSE(PalindromeChecker::isPalindrome("ab"));
    EXPECT_FALSE(PalindromeChecker::isPalindrome("abc"));
    EXPECT_FALSE(PalindromeChecker::isPalindrome("abca"));
}

TEST(PalindromeTest, IsPalindromeIgnoreCase)
{
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase("Racecar"));
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase("MadAm"));
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase("A"));
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase(""));
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase("ABBA"));
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase("AbBa"));
    EXPECT_TRUE(PalindromeChecker::isPalindromeIgnoreCase("aBbA"));
    
    EXPECT_FALSE(PalindromeChecker::isPalindromeIgnoreCase("Hello"));
    EXPECT_FALSE(PalindromeChecker::isPalindromeIgnoreCase("World"));
    EXPECT_FALSE(PalindromeChecker::isPalindromeIgnoreCase("Abc"));
    EXPECT_FALSE(PalindromeChecker::isPalindromeIgnoreCase("Test"));
}

TEST(PalindromeTest, IsPalindrome_NegativeNumber)
{
    EXPECT_THROW(PalindromeChecker::isPalindrome(-1), invalid_argument);
    EXPECT_THROW(PalindromeChecker::isPalindrome(-121), invalid_argument);
    EXPECT_THROW(PalindromeChecker::isPalindrome(-12321), invalid_argument);
    EXPECT_THROW(PalindromeChecker::isPalindrome(-10), invalid_argument);
}

TEST(PalindromeTest, IsPalindrome_LargeNumbers)
{
    EXPECT_TRUE(PalindromeChecker::isPalindrome(123454321));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(987656789));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(123456789));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(987654321));
}

TEST(PalindromeTest, IsPalindrome_SpecialCases)
{
    EXPECT_TRUE(PalindromeChecker::isPalindrome(1));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(11));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(111));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(1111));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(101));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(1001));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(10001));
}