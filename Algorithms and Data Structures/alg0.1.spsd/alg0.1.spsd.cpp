#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    vector<int> H(n + 1);
    for(int i = 1; i <= n; i++)
    {
        in >> H[i];
    }

    for (int i = 1; 2 * i <= n; i++)
    {
        int l = 2 * i;
        int r = 2 * i + 1;
        if (l <= n && H[i] > H[l])
        {
            out << "No";
            return 0;
        }
        if (r <= n && H[i] > H[r])
        {
            out << "No";
            return 0;
        }
    }

    out << "Yes";

    return 0;
}