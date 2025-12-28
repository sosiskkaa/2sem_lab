#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class PalindromeChecker 
{
public:
    static bool isPalindrome(int number);
    static bool isPalindrome(const string& str);
    static bool isPalindromeIgnoreCase(const string& str);

private:
    static void validateInput(int number);
    static string numberToString(int number);
    static string toLower(const string& str);
};