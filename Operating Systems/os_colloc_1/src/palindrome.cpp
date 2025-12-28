#include "palindrome.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace std;

void PalindromeChecker::validateInput(int number) 
{
    if (number < 0) 
    {
        throw invalid_argument("Negative numbers cannot be palindromes");
    }
}

string PalindromeChecker::numberToString(int number) 
{
    if (number == 0) 
    {
        return "0";
    }

    string result;
    while (number > 0) 
    {
        result += static_cast<char>('0' + (number % 10));
        number /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

string PalindromeChecker::toLower(const string& str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) 
              { 
                  return tolower(c); 
              });
    return result;
}

bool PalindromeChecker::isPalindrome(int number) 
{
    validateInput(number);

    if (number < 10) 
    {
        return true;
    }

    string str = numberToString(number);
    return isPalindrome(str);
}

bool PalindromeChecker::isPalindrome(const string& str) 
{
    if (str.empty()) 
    {
        return true;
    }

    size_t left = 0;
    size_t right = str.length() - 1;

    while (left < right) 
    {
        if (str[left] != str[right]) 
        {
            return false;
        }
        ++left;
        --right;
    }

    return true;
}

bool PalindromeChecker::isPalindromeIgnoreCase(const string& str)
{
    if (str.empty())
    {
        return true;
    }

    string lowerStr = toLower(str);
    return isPalindrome(lowerStr);
}