#pragma once
#include <vector>
#include <stdexcept>

using namespace std;

class FibonacciGenerator 
{
public:
    static vector<unsigned long long> generateFirstN(size_t n);
    static bool canSafelyGenerate(size_t n);

private:
    static void validateInput(size_t n);
    static const size_t MAX_SAFE_N = 93;
};