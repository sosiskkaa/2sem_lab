#include "fibonacci.h"
#include <stdexcept>

using namespace std;

void FibonacciGenerator::validateInput(size_t n) 
{
    if (n == 0) 
    {
        throw invalid_argument("input must be a positive integer");
    }

    if (n > 93) 
    {
        throw overflow_error("requested fibonacci sequence would cause integer overflow");
    }
}

vector<unsigned long long> FibonacciGenerator::generateFirstN(size_t n) 
{
    validateInput(n);

    vector<unsigned long long> result;
    result.reserve(n);

    if (n >= 1) 
    {
        result.push_back(0);
    }
    if (n >= 2) 
    {
        result.push_back(1);
    }

    for (size_t i = 2; i < n; ++i) 
    {
        if (result[i - 1] > numeric_limits<unsigned long long>::max() - result[i - 2]) 
        {
            throw overflow_error("fibonacci sequence computation would cause integer overflow");
        }

        unsigned long long next = result[i - 1] + result[i - 2];
        result.push_back(next);
    }

    return result;
}