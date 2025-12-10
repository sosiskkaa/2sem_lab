#include <fstream>
#include <climits>

using namespace std;

int main()
{
    ifstream in("bst.in");
    ofstream out("bst.out");

    int n;
    in >> n;

    long long* V = new long long[n];
    long long* granf = new long long[n];
    long long* grans = new long long[n];

    in >> V[0];
    granf[0] = -214748370000LL;
    grans[0] = 214748370000LL;

    for (int i = 1; i < n; i++)
    {
        int pred;
        char lr;
        in >> V[i] >> pred >> lr;
        pred -= 1;

        if (lr == 'L')
        {
            granf[i] = granf[pred];
            grans[i] = V[pred];
        }
        else
        {
            granf[i] = V[pred];
            grans[i] = grans[pred];
        }
        if (V[i] < granf[i] || V[i] >= grans[i])
        {
            out << "NO";
            return 0;
        }
    }

    out << "YES";
    return 0;
}
