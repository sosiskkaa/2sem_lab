#pragma once
#include <memory>
#include <stdexcept>
#include <vector>
#include <functional>

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
        
        Node(T&& value) : data(move(value)), next(nullptr) {}
    };

    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    LinkedList(const LinkedList& other);
    
    LinkedList& operator=(const LinkedList& other);
    
    ~LinkedList() = default;

    void add(const T& value);
    
    void add(T&& value);
    
    void insert(size_t index, const T& value);
    
    void remove(size_t index);
    
    T get(size_t index) const;
    
    bool contains(const T& value) const;
    
    void clear();
    
    void reverseIterative();
    
    void reverseRecursive();
    
    void forEach(const function<void(const T&)>& func) const;
    
    vector<T> toVector() const;
    
    size_t getSize() const 
    { 
        return size; 
    }
    
    bool isEmpty() const 
    { 
        return size == 0; 
    }
    
    T getFirst() const;
    
    T getLast() const;

private:
    shared_ptr<Node> reverseRecursiveHelper(shared_ptr<Node> node);
    void validateIndex(size_t index) const;
    void validateNotEmpty() const;
};

#include "linklist_impl.h"