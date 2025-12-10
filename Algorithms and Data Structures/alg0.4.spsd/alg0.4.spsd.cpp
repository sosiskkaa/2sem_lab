#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ifstream in("huffman.in");
    ofstream out("huffman.out");

    long long n;
    in >> n;

    vector<long long> merg, freq(n);
    for (int i = 0; i < n; ++i) 
    {
        in >> freq[i];
    }

    int i = 0, j = 0;
    long long res = 0;

    while (i + j < n + merg.size() - 1) 
    {
        long long a, b;
        if (i < n && (j >= merg.size() || freq[i] <= merg[j])) 
        {
            a = freq[i++];
        }
        else 
        {
            a = merg[j++];
        }

        if (i < n && (j >= merg.size() || freq[i] <= merg[j])) 
        {
            b = freq[i++];
        }
        else 
        {
            b = merg[j++];
        }

        res += a + b;
        merg.push_back(a + b);
    }

    out << res;

    return 0;
}
