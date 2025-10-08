#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
// a mezhdy b c --> k iz [b;c]
int razl(int a, int b, int c)
{
    if (a < b)
        return -1;
    if (a <= c && a >= b)
        return 1;
    if (c == 1)
        return -1;

    int k = INT_MAX;
    
    for (int i = c; i >= b; i--)
    {
        if (a % i == 0)
        {
            long long chast = a / i;
            if (chast == 1)
            {
                k = min(k, 1);
                continue;
            }
			int temp = razl(chast, b, c);
			if (temp != -1)
				k = min(k, temp + 1);

        }
    }
    if (k == INT_MAX)
        return -1;
    else
        return k;
}

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");
    long long a;
    int b, c;
    in >> a >> b >> c;
    out << razl(a, b, c);

    return 0;
}