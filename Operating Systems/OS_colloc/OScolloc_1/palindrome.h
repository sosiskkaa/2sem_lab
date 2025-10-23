#pragma once
#include <string>
#include <cmath>

using namespace std;

class PalindromeChecker 
{
public:
    static bool isPalindrome(int number);
    static bool isPalindrome(const string& str);

private:
    static void validateInput(int number);
    static string numberToString(int number);
};