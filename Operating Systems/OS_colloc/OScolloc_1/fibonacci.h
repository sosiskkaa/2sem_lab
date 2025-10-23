#pragma once
#include <vector>
#include <stdexcept>

using namespace std;

class FibonacciGenerator 
{
public:
    static vector<unsigned long long> generateFirstN(size_t n);

private:
    static void validateInput(size_t n);
};