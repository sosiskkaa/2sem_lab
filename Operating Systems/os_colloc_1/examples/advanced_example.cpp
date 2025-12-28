#include <iostream>
#include <iomanip>
#include "fibonacci.h"
#include "palindrome.h"
#include "linklist.h"

using namespace std;

void printFibonacciWithPalindromes()
{
    cout << "=== Fibonacci Numbers and Palindromes ===" << endl;
    
    try
    {
        auto fibNumbers = FibonacciGenerator::generateFirstN(20);
        
        cout << left << setw(10) << "Fibonacci" 
             << setw(15) << "Palindrome?" 
             << "Binary Palindrome?" << endl;
        cout << string(45, '-') << endl;
        
        for (auto num : fibNumbers)
        {
            bool isDecPalindrome = false;
            bool isBinPalindrome = false;
            
            try
            {
                isDecPalindrome = PalindromeChecker::isPalindrome(static_cast<int>(num));
            }
            catch (const exception&) {}
            
            string binaryStr;
            unsigned long long temp = num;
            while (temp > 0)
            {
                binaryStr = (temp % 2 ? "1" : "0") + binaryStr;
                temp /= 2;
            }
            if (num == 0) 
            {
                binaryStr = "0";
            }
            
            isBinPalindrome = PalindromeChecker::isPalindrome(binaryStr);
            
            cout << setw(10) << num 
                 << setw(15) << (isDecPalindrome ? "Yes" : "No")
                 << (isBinPalindrome ? "Yes" : "No") << endl;
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void demonstrateLinkedListOperations()
{
    cout << "\n=== Linked List Operations ===" << endl;
    
    LinkedList<string> list;
    
    list.add("Hello");
    list.add("World");
    list.add("from");
    list.add("C++");
    list.add("LinkedList");
    
    cout << "Original list: ";
    list.forEach([](const string& s) 
    { 
        cout << s << " "; 
    });
    cout << endl;
    
    list.reverseIterative();
    cout << "After reversal: ";
    list.forEach([](const string& s) 
    { 
        cout << s << " "; 
    });
    cout << endl;
    
    list.insert(2, "Reversed");
    cout << "After insertion: ";
    list.forEach([](const string& s) 
    { 
        cout << s << " "; 
    });
    cout << endl;
    
    list.remove(3);
    cout << "After removal: ";
    list.forEach([](const string& s) 
    { 
        cout << s << " "; 
    });
    cout << endl;
    
    cout << "Contains 'C++': " << (list.contains("C++") ? "Yes" : "No") << endl;
    cout << "Contains 'Java': " << (list.contains("Java") ? "Yes" : "No") << endl;
}

void advancedPalindromeChecks()
{
    cout << "\n=== Advanced Palindrome Checks ===" << endl;
    
    vector<string> testStrings = 
    {
        "Racecar",
        "A man, a plan, a canal: Panama",
        "Madam",
        "Hello World",
        "12321",
        "No 'x' in Nixon"
    };
    
    for (const auto& str : testStrings)
    {
        string cleaned;
        for (char c : str)
        {
            if (isalnum(c))
            {
                cleaned += tolower(c);
            }
        }
        
        bool isPal = PalindromeChecker::isPalindrome(cleaned);
        cout << "\"" << str.substr(0, 20) << "...\" "
             << (isPal ? "is a palindrome" : "is not a palindrome") << endl;
    }
}

int main()
{
    cout << "Advanced Examples for Fibonacci, Palindrome, and LinkedList" << endl;
    cout << string(60, '=') << endl;
    
    printFibonacciWithPalindromes();
    demonstrateLinkedListOperations();
    advancedPalindromeChecks();
    
    return 0;
}