#include <gtest/gtest.h>
#include "linklist.h"

using namespace std;

TEST(LinkedListTest, DefaultConstructor)
{
    LinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(LinkedListTest, AddAndSize)
{
    LinkedList<int> list;
    
    list.add(1);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 1);
    
    list.add(2);
    EXPECT_EQ(list.getSize(), 2);
    
    list.add(3);
    EXPECT_EQ(list.getSize(), 3);
}

TEST(LinkedListTest, Get)
{
    LinkedList<int> list;
    
    list.add(10);
    list.add(20);
    list.add(30);
    
    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 20);
    EXPECT_EQ(list.get(2), 30);
}

TEST(LinkedListTest, Get_InvalidIndex)
{
    LinkedList<int> list;
    
    EXPECT_THROW(list.get(0), out_of_range);
    
    list.add(1);
    EXPECT_NO_THROW(list.get(0));
    EXPECT_THROW(list.get(1), out_of_range);
    EXPECT_THROW(list.get(10), out_of_range);
}

TEST(LinkedListTest, GetFirstAndLast)
{
    LinkedList<int> list;
    
    list.add(1);
    EXPECT_EQ(list.getFirst(), 1);
    EXPECT_EQ(list.getLast(), 1);
    
    list.add(2);
    list.add(3);
    
    EXPECT_EQ(list.getFirst(), 1);
    EXPECT_EQ(list.getLast(), 3);
}

TEST(LinkedListTest, GetFirstAndLast_EmptyList)
{
    LinkedList<int> list;
    
    EXPECT_THROW(list.getFirst(), runtime_error);
    EXPECT_THROW(list.getLast(), runtime_error);
}

TEST(LinkedListTest, ReverseIterative)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i);
    }
    
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(list.toVector(), expected);
    
    list.reverseIterative();
    
    reverse(expected.begin(), expected.end());
    EXPECT_EQ(list.toVector(), expected);
    
    list.reverseIterative();
    reverse(expected.begin(), expected.end());
    EXPECT_EQ(list.toVector(), expected);
}

TEST(LinkedListTest, ReverseRecursive)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i);
    }
    
    list.reverseRecursive();
    vector<int> expected = {5, 4, 3, 2, 1};
    EXPECT_EQ(list.toVector(), expected);
}

TEST(LinkedListTest, Reverse_EmptyList)
{
    LinkedList<int> list;
    
    EXPECT_NO_THROW(list.reverseIterative());
    EXPECT_NO_THROW(list.reverseRecursive());
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListTest, Reverse_SingleElement)
{
    LinkedList<int> list;
    list.add(42);
    
    list.reverseIterative();
    EXPECT_EQ(list.getFirst(), 42);
    EXPECT_EQ(list.getLast(), 42);
    EXPECT_EQ(list.getSize(), 1);
    
    list.reverseRecursive();
    EXPECT_EQ(list.getFirst(), 42);
    EXPECT_EQ(list.getLast(), 42);
    EXPECT_EQ(list.getSize(), 1);
}

TEST(LinkedListTest, Insert)
{
    LinkedList<int> list;
    
    list.insert(0, 1);
    EXPECT_EQ(list.toVector(), vector<int>({1}));
    
    list.insert(1, 3);
    EXPECT_EQ(list.toVector(), vector<int>({1, 3}));
    
    list.insert(1, 2);
    EXPECT_EQ(list.toVector(), vector<int>({1, 2, 3}));
    
    list.insert(0, 0);
    EXPECT_EQ(list.toVector(), vector<int>({0, 1, 2, 3}));
    
    list.insert(4, 4);
    EXPECT_EQ(list.toVector(), vector<int>({0, 1, 2, 3, 4}));
}

TEST(LinkedListTest, Insert_InvalidIndex)
{
    LinkedList<int> list;
    
    EXPECT_THROW(list.insert(1, 1), out_of_range);
    EXPECT_THROW(list.insert(10, 1), out_of_range);
    
    list.add(1);
    EXPECT_NO_THROW(list.insert(1, 2));
    EXPECT_THROW(list.insert(3, 3), out_of_range);
}

TEST(LinkedListTest, Remove)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i);
    }
    
    list.remove(2);
    EXPECT_EQ(list.toVector(), vector<int>({1, 2, 4, 5}));
    
    list.remove(0);
    EXPECT_EQ(list.toVector(), vector<int>({2, 4, 5}));
    
    list.remove(2);
    EXPECT_EQ(list.toVector(), vector<int>({2, 4}));
    
    list.remove(1);
    EXPECT_EQ(list.toVector(), vector<int>({2}));
    
    list.remove(0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListTest, Remove_InvalidIndex)
{
    LinkedList<int> list;
    
    EXPECT_THROW(list.remove(0), out_of_range);
    
    list.add(1);
    EXPECT_THROW(list.remove(1), out_of_range);
    EXPECT_THROW(list.remove(10), out_of_range);
}

TEST(LinkedListTest, Contains)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i * 10);
    }
    
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(30));
    EXPECT_TRUE(list.contains(50));
    EXPECT_FALSE(list.contains(15));
    EXPECT_FALSE(list.contains(0));
    EXPECT_FALSE(list.contains(100));
}

TEST(LinkedListTest, Clear)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i);
    }
    
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 5);
    
    list.clear();
    
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_THROW(list.getFirst(), runtime_error);
}

TEST(LinkedListTest, CopyConstructor)
{
    LinkedList<int> list1;
    
    for (int i = 1; i <= 5; ++i)
    {
        list1.add(i);
    }
    
    LinkedList<int> list2(list1);
    
    EXPECT_EQ(list1.getSize(), 5);
    EXPECT_EQ(list2.getSize(), 5);
    EXPECT_EQ(list1.toVector(), list2.toVector());
    
    list1.add(6);
    EXPECT_EQ(list1.getSize(), 6);
    EXPECT_EQ(list2.getSize(), 5);
}

TEST(LinkedListTest, AssignmentOperator)
{
    LinkedList<int> list1;
    
    for (int i = 1; i <= 5; ++i)
    {
        list1.add(i);
    }
    
    LinkedList<int> list2;
    list2 = list1;
    
    EXPECT_EQ(list1.getSize(), 5);
    EXPECT_EQ(list2.getSize(), 5);
    EXPECT_EQ(list1.toVector(), list2.toVector());
    
    list1.add(6);
    EXPECT_EQ(list1.getSize(), 6);
    EXPECT_EQ(list2.getSize(), 5);
    
    list2 = list1;
    EXPECT_EQ(list2.getSize(), 6);
    EXPECT_EQ(list1.toVector(), list2.toVector());
}

TEST(LinkedListTest, SelfAssignment)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i);
    }
    
    list = list;
    
    EXPECT_EQ(list.getSize(), 5);
    EXPECT_EQ(list.toVector(), vector<int>({1, 2, 3, 4, 5}));
}

TEST(LinkedListTest, ForEach)
{
    LinkedList<int> list;
    
    for (int i = 1; i <= 5; ++i)
    {
        list.add(i);
    }
    
    int sum = 0;
    list.forEach([&sum](const int& value) 
    { 
        sum += value; 
    });
    
    EXPECT_EQ(sum, 15);
    
    vector<int> collected;
    list.forEach([&collected](const int& value) 
    { 
        collected.push_back(value); 
    });
    
    EXPECT_EQ(collected, vector<int>({1, 2, 3, 4, 5}));
}

TEST(LinkedListTest, StringList)
{
    LinkedList<string> list;
    
    list.add("Hello");
    list.add("World");
    list.add("Test");
    
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getFirst(), "Hello");
    EXPECT_EQ(list.getLast(), "Test");
    EXPECT_TRUE(list.contains("World"));
    EXPECT_FALSE(list.contains("Missing"));
    
    list.reverseIterative();
    EXPECT_EQ(list.getFirst(), "Test");
    EXPECT_EQ(list.getLast(), "Hello");
}

TEST(LinkedListTest, ComplexTypes)
{
    LinkedList<vector<int>> list;
    
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {4, 5, 6};
    vector<int> v3 = {7, 8, 9};
    
    list.add(v1);
    list.add(v2);
    list.add(v3);
    
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.get(0), v1);
    EXPECT_EQ(list.get(1), v2);
    EXPECT_EQ(list.get(2), v3);
    
    list.reverseIterative();
    EXPECT_EQ(list.get(0), v3);
    EXPECT_EQ(list.get(1), v2);
    EXPECT_EQ(list.get(2), v1);
}