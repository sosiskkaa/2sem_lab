#include "fibonacci.h"
#include <stdexcept>
#include <limits>

using namespace std;

void FibonacciGenerator::validateInput(size_t n) 
{
    if (n == 0) 
    {
        throw invalid_argument("Input must be a positive integer");
    }

    if (!canSafelyGenerate(n))
    {
        throw overflow_error("Requested Fibonacci sequence would cause integer overflow");
    }
}

bool FibonacciGenerator::canSafelyGenerate(size_t n)
{
    return n <= MAX_SAFE_N;
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
            throw overflow_error("Fibonacci sequence computation would cause integer overflow");
        }

        unsigned long long next = result[i - 1] + result[i - 2];
        result.push_back(next);
    }

    return result;
}