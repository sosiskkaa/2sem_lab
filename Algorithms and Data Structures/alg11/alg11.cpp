#include <algorithm>
#include <fstream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

vector<long long> del(long long a, int b, int c);

unordered_map<long long, long long> mem;
long long razl(long long a, int b, int c, int depth = 0)
{
    const int MAX_DEPTH = 500;
    if (depth > MAX_DEPTH)
        return -1;
    if (a <= c && a >= b)
        return 1;
    if (mem.count(a))
        return mem[a];

    long long k = LLONG_MAX;

	vector<long long> D = del(a, b, c);
    for (long long i : D)
    {
        if (a % i == 0)
        {
            long long chast = a / i;
            if (chast == 1)
            {
                if (k > 1)
                    k = 1;
                continue;
            }
			long long temp = razl(chast, b, c, depth + 1);
            if (temp != -1)
                if (k > temp + 1)
                    k = temp + 1;

        }
    }
    mem[a] = (k == LLONG_MAX ? -1 : k);
    return mem[a];
}

vector<long long> del(long long a, int b, int c) 
{
    vector<long long> res;
    for (long long i = 1; i * i <= a; ++i) 
    {
        if (a % i == 0) 
        {
            if (i >= b && i <= c) 
                res.push_back(i);
            long long d = a / i;
            if (d >= b && d <= c && d != i) 
                res.push_back(d);
        }
    }
    sort(res.rbegin(), res.rend());
    return res;
}

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");
    long long a;
    int b, c;
    in >> a >> b >> c;

    if (a < b)
    {
        out << -1;
        return 0;
    }
    if (c == 1)
    {
        out << -1;
        return 0;
    }
    if (b == 1)
        b += 1;

    out << razl(a, b, c, 0);

    return 0;
}