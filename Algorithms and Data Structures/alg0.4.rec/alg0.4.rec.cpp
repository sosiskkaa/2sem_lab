#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int poryad(vector<int> Matr)
{
    int n = Matr.size();
    vector<vector<int>> M(n, vector<int>(n, 0));

    for (int i = 2; i < n; i++)
    {
        for (int j = 1; j < n - i + 1; j++)
        {
            int k = j + i - 1;
            M[j][k] = INT_MAX;
            for (int q = j; q < k; q++)
            {
                int por = M[j][q] + M[q + 1][k] + Matr[j - 1] * Matr[q] * Matr[k];
                if (por < M[j][k])
                    M[j][k] = por;
            }
        }
    }

    return M[1][n - 1];
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    int s;
    in >> s;

    vector<int> Matr(s + 1);
    in >> Matr[0];

    int temp;
    for (int i = 1; i < s + 1; i++)
    {
        in >> Matr[i];
        in >> temp;
    }

    out << poryad(Matr);

    return 0;
}