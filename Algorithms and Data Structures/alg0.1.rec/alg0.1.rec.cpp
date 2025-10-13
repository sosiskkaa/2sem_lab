#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> M(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> M[i];
    }

    vector<long long> V(n + 1);
    vector<int> P(n + 1, -1);

    if (n == 1) 
    { 
        cout << M[1] << endl << 1; 
        return 0; 
    } 
    if (n == 2)
    {
        cout << -1;
        return 0;
    }
    if (n == 3) 
    {
        cout << M[3] + M[1] << endl << "1 3";
        return 0;
    }
    if (n == 4)
    {
        cout << M[4] + M[1] << endl << "1 4";
        return 0;
    }


    V[1] = M[1];
    V[2] = LLONG_MIN;
    V[3] = M[3] + M[1]; P[3] = 1;
    V[4] = M[4] + M[1]; P[4] = 1;

    for (int i = 5; i <= n; i++)
    {
        if (V[i - 2] > V[i - 3])
        {
            V[i] = V[i - 2] + M[i];
            P[i] = i - 2;
        }
        else
        {
            V[i] = V[i - 3] + M[i];
            P[i] = i - 3;
        }
    }

    if (V[n] == -1)
    {
        cout << -1;
        return 0;
    }

    vector<int> Path;
    int i = n;
    while (i > 0)
    {
        Path.push_back(i);
        i = P[i];
    }
    cout << V[n] << endl;

    reverse(Path.begin(), Path.end());
    for (int p : Path)
    {
        cout << p << " ";
    }

    return 0;
}
