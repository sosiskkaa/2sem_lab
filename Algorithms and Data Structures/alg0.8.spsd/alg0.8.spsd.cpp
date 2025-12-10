#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DerOtr
{
    int n;
    vector<long long> T;
public:
    DerOtr(const vector<int>& X) : n(X.size())
    {
        T.resize(n * 4);
        build(X, 1, 0, n - 1);
    }

    void build(const vector<int>& X, int v, int tl, int tr) 
    {
        if (tl == tr) 
        {
            T[v] = X[tl];
        }
        else 
        {
            int t = (tl + tr) / 2;
            build(X, v * 2, tl, t);
            build(X, v * 2 + 1, t + 1, tr);
            T[v] = T[v * 2] + T[v * 2 + 1];
        }
    }

    void add(int pos, int val, int v, int tl, int tr) {
        if (tl == tr) 
        {
            T[v] += val;
        }
        else 
        {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                add(pos, val, v * 2, tl, tm);
            else
                add(pos, val, v * 2 + 1, tm + 1, tr);

            T[v] = T[v * 2] + T[v * 2 + 1];
        }
    }

    long long sum(int l, int r, int v, int tl, int tr) 
    {
        if (l > r) return 0;
        if (l == tl && r == tr) return T[v];
        int tm = (tl + tr) / 2;

        long long res = sum(l, min(r, tm), v * 2, tl, tm) + sum(max(l, tm + 1), r, v * 2 + 1, tm + 1, tr);
        return res;
    }
};

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> X(n);
    for (int i = 0; i < n; i++) 
    {
        cin >> X[i];
    }

    DerOtr D(X);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        string s;
        cin >> s;

        if (s == "FindSum") 
        {
            int l, r;
            cin >> l >> r;
            cout << D.sum(l, r - 1, 1, 0, n - 1) << endl;
        }
        else 
        {
            int i, x;
            cin >> i >> x;
            D.add(i, x, 1, 0, n - 1);
        }
    }

    return 0;
}
