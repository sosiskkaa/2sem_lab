#ifndef LINKLIST_IMPL_H
#define LINKLIST_IMPL_H

#include "linklist.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0)
{
    auto current = other.head;
    while (current)
    {
        add(current->data);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
{
    if (this != &other)
    {
        clear();
        auto current = other.head;
        while (current)
        {
            add(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void LinkedList<T>::add(const T& value)
{
    auto newNode = make_shared<Node>(value);
    
    if (!head)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::add(T&& value)
{
    auto newNode = make_shared<Node>(move(value));
    
    if (!head)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::insert(size_t index, const T& value)
{
    if (index > size)
    {
        throw out_of_range("Index " + to_string(index) + 
                          " is out of range for list of size " + 
                          to_string(size));
    }
    
    if (index == 0)
    {
        auto newNode = make_shared<Node>(value);
        newNode->next = head;
        head = newNode;
        if (!tail) 
        {
            tail = newNode;
        }
    }
    else if (index == size)
    {
        add(value);
        return;
    }
    else
    {
        auto current = head;
        for (size_t i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        
        auto newNode = make_shared<Node>(value);
        newNode->next = current->next;
        current->next = newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::remove(size_t index)
{
    if (index >= size)
    {
        throw out_of_range("Index " + to_string(index) + 
                          " is out of range for list of size " + 
                          to_string(size));
    }
    
    if (size == 0)
    {
        throw runtime_error("Cannot remove from empty list");
    }
    
    if (index == 0)
    {
        head = head->next;
        if (!head) 
        {
            tail = nullptr;
        }
    }
    else
    {
        auto current = head;
        for (size_t i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        
        current->next = current->next->next;
        if (index == size - 1)
        {
            tail = current;
        }
    }
    --size;
}

template<typename T>
T LinkedList<T>::get(size_t index) const
{
    if (index >= size)
    {
        throw out_of_range("Index " + to_string(index) + 
                          " is out of range for list of size " + 
                          to_string(size));
    }
    
    if (size == 0)
    {
        throw runtime_error("List is empty");
    }
    
    auto current = head;
    for (size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }
    
    return current->data;
}

template<typename T>
bool LinkedList<T>::contains(const T& value) const
{
    auto current = head;
    while (current)
    {
        if (current->data == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void LinkedList<T>::clear()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
void LinkedList<T>::reverseIterative()
{
    if (!head || !head->next)
    {
        return;
    }
    
    tail = head;
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
void LinkedList<T>::reverseRecursive()
{
    tail = head;
    head = reverseRecursiveHelper(head);
}

template<typename T>
shared_ptr<typename LinkedList<T>::Node> LinkedList<T>::reverseRecursiveHelper(
    shared_ptr<Node> node)
{
    if (!node || !node->next)
    {
        return node;
    }
    
    auto newHead = reverseRecursiveHelper(node->next);
    node->next->next = node;
    node->next = nullptr;
    return newHead;
}

template<typename T>
void LinkedList<T>::forEach(const function<void(const T&)>& func) const
{
    auto current = head;
    while (current)
    {
        func(current->data);
        current = current->next;
    }
}

template<typename T>
vector<T> LinkedList<T>::toVector() const
{
    vector<T> result;
    result.reserve(size);
    
    auto current = head;
    while (current)
    {
        result.push_back(current->data);
        current = current->next;
    }
    
    return result;
}

template<typename T>
T LinkedList<T>::getFirst() const
{
    if (size == 0)
    {
        throw runtime_error("List is empty");
    }
    return head->data;
}

template<typename T>
T LinkedList<T>::getLast() const
{
    if (size == 0)
    {
        throw runtime_error("List is empty");
    }
    return tail->data;
}

template<typename T>
void LinkedList<T>::validateIndex(size_t index) const
{
    if (index > size)
    {
        throw out_of_range("Index " + to_string(index) + 
                          " is out of range for list of size " + 
                          to_string(size));
    }
}

template<typename T>
void LinkedList<T>::validateNotEmpty() const
{
    if (isEmpty())
    {
        throw runtime_error("List is empty");
    }
}

#endif