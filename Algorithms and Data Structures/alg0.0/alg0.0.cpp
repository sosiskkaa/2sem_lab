#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    set<long long> chisl;
    long long temp, sum = 0;

    while (in >> temp)
    {
        chisl.insert(temp);
    }

    for (long long ch : chisl)
    {
        sum += ch;
    }

    out << sum;
}