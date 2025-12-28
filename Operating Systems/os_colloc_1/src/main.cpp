#include <iostream>
#include "fibonacci.h"
#include "palindrome.h"
#include "linklist.h"

using namespace std;

int main() 
{
    cout << "Fibonacci Example" << endl;
    
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

    cout << "\nPalindrome Checks" << endl;
    
    vector<int> testNumbers = { 121, 123, 1221, 12321, 12345, -1, 0, 7 };
    
    for (int num : testNumbers) 
    {
        try 
        {
            bool isPal = PalindromeChecker::isPalindrome(num);
            cout << num << " is " << (isPal ? "a palindrome" : "not a palindrome") << endl;
        }
        catch (const exception& e) 
        {
            cerr << "Error checking " << num << ": " << e.what() << endl;
        }
    }

    cout << "\nString Palindrome Checks" << endl;
    
    vector<string> testStrings = { "racecar", "hello", "A", "", "Madam" };
    
    for (const string& str : testStrings) 
    {
        try 
        {
            bool isPal = PalindromeChecker::isPalindromeIgnoreCase(str);
            cout << "\"" << str << "\" is " << (isPal ? "a palindrome" : "not a palindrome") << endl;
        }
        catch (const exception& e) 
        {
            cerr << "Error checking \"" << str << "\": " << e.what() << endl;
        }
    }

    cout << "\nLinkedList Operations" << endl;
    
    LinkedList<int> list;
    
    try 
    {
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

        cout << "First element: " << list.getFirst() << endl;
        cout << "Last element: " << list.getLast() << endl;
        cout << "List size: " << list.getSize() << endl;

        list.insert(2, 99);
        cout << "After inserting 99 at index 2: ";
        for (auto val : list.toVector()) 
        {
            cout << val << " ";
        }
        cout << endl;

        list.remove(3);
        cout << "After removing element at index 3: ";
        for (auto val : list.toVector()) 
        {
            cout << val << " ";
        }
        cout << endl;

        cout << "Contains 99? " << (list.contains(99) ? "Yes" : "No") << endl;
        cout << "Contains 100? " << (list.contains(100) ? "Yes" : "No") << endl;

        LinkedList<int> copiedList = list;
        cout << "Copied list: ";
        for (auto val : copiedList.toVector()) 
        {
            cout << val << " ";
        }
        cout << endl;

        list.clear();
        cout << "After clear, list is empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
        
        cout << "\nTesting error handling:" << endl;
        
        try 
        {
            int val = list.getFirst();
        }
        catch (const exception& e) 
        {
            cerr << "Expected error getting first from empty list: " << e.what() << endl;
        }

        try 
        {
            list.insert(10, 42);
        }
        catch (const exception& e) 
        {
            cerr << "Expected error inserting at invalid index: " << e.what() << endl;
        }

        try 
        {
            list.remove(0);
        }
        catch (const exception& e) 
        {
            cerr << "Expected error removing from empty list: " << e.what() << endl;
        }
    }
    catch (const exception& e) 
    {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}