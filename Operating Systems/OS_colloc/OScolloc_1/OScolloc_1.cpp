#include <iostream>
#include "fibonacci.h"
#include "palindrome.h"
#include "linklist.h"

using namespace std;

int main() 
{
    cout << "fibonacci" << endl;
    try 
    {
        auto fibNumbers = FibonacciGenerator::generateFirstN(15);
        cout << "First 15 Fibonacci numbers: ";
        for (auto num : fibNumbers) 
        {
            cout << num << " ";
        }
        cout << endl;
    }
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "\npalindrome" << endl;
    vector<int> testNumbers = { 121, 123, 1221, 12321, 12345 };
    for (int num : testNumbers) 
    {
        try 
        {
            bool isPal = PalindromeChecker::isPalindrome(num);
            cout << num << " is " << (isPal ? "a palindrome" : "not a palindrome") << endl;
        }
        catch (const exception& e) 
        {
            cerr << "error checking " << num << ": " << e.what() << endl;
        }
    }

    cout << "\nlinklist reverce" << endl;
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i) 
    {
        list.add(i);
    }

    cout << "Original list: ";
    for (auto val : list.toVector()) 
    {
        cout << val << " ";
    }
    cout << endl;

    list.reverseIterative();

    cout << "Reversed list: ";
    for (auto val : list.toVector()) 
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}