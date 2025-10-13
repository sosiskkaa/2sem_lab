#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{

	ifstream in("input.txt");
	ofstream out("output.txt");

	int n;
	in >> n;

	vector<long long> V(n), P;
	for (int i = 0; i < n; i++)
		in >> V[i];

    P.push_back(V[0]);

	for (int i = 1; i < n; i++)
	{
		if (V[i] > P.back())
			P.push_back(V[i]);
		else
		{
			int pos = lower_bound(P.begin(), P.end(), V[i]) - P.begin();
			P[pos] = V[i];
		}
	}

	out << P.size();

	return 0;
}