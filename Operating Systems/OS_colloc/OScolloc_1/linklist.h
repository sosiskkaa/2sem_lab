#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class LinkedList 
{
private:
    struct Node 
    {
        T data;
        shared_ptr<Node> next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    shared_ptr<Node> head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}

    void add(const T& value);
    void reverseIterative();
    vector<T> toVector() const;
    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
};

template<typename T>
void LinkedList<T>::add(const T& value) 
{
    auto newNode = make_shared<Node>(value);

    if (!head) 
    {
        head = newNode;
    }
    else 
    {
        auto current = head;
        while (current->next) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::reverseIterative() 
{
    if (!head || !head->next) 
    {
        return;
    }

    shared_ptr<Node> prev = nullptr;
    auto current = head;
    shared_ptr<Node> next = nullptr;

    while (current) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

template<typename T>
vector<T> LinkedList<T>::toVector() const 
{
    vector<T> result;
    auto current = head;

    while (current) 
    {
        result.push_back(current->data);
        current = current->next;
    }

    return result;
}