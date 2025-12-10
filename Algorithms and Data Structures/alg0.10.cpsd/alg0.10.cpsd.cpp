#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int m, c, n;
    in >> m >> c >> n;

    vector<int> H(m, -1);

    for (int j = 0; j < n; j++)
    {
        int x;
        in >> x;

        for (int i = 0; i < m; i++)
        {
            int h = (x % m + c * i) % m;
            if (H[h] == x)
                break;
            if (H[h] == -1)
            {
                H[h] = x;
                break;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        out << H[i] << " ";
    }

    return 0;
}