#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);
    vector<vector<int>> F(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

	for (int i = 0; i < n; i++)
	{
		cin >> B[i];
	}

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

	cout << F[n][n] << endl;

	vector<int> Ai, Bi;
	int i = n, j = n;

	while (i != 0 && j != 0)
	{
		if (A[i - 1] == B[j - 1])
		{
			Ai.push_back(i - 1);
			Bi.push_back(j - 1);
			i--; j--;
		}
		else if (F[i - 1][j] > F[i][j - 1])
			i--;
		else
			j--;
	}

	reverse(Ai.begin(), Ai.end());
	reverse(Bi.begin(), Bi.end());

	for (int i : Ai)
	{
		cout << i << " ";
	}
	cout << endl;
	for (int i : Bi)
	{
		cout << i << " ";
	}

    return 0;
}