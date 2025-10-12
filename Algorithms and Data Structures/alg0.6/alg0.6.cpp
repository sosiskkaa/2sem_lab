#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");

    string A;
    in >> A;

    string B = A; 
    reverse(B.begin(), B.end());

    int n = A.size();
    vector<vector<int>> F(n + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (A[i - 1] == B[j - 1])
			{
				F[i][j] = F[i - 1][j - 1] + 1;
			}
			else
			{
				F[i][j] = max(F[i - 1][j], F[i][j - 1]);
			}
		}
	}

	out << F[n][n] << endl;

	string Ai;
	int i = n, j = n;

	while (i != 0 && j != 0)
	{
		if (A[i - 1] == B[j - 1])
		{
			Ai += A[i - 1];
			i--; j--;
		}
		else if (F[i - 1][j] > F[i][j - 1])
			i--;
		else
			j--;
	}

	out << Ai;

    return 0;
}