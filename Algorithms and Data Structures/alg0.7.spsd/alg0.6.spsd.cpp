#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class DSU
{
    vector<int> parent, size;
    int comps;
public:
    DSU(int n) : parent(n), size(n, 1), comps(n)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int x)
    {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            comps--;
        }
    }
    int getComps()
    {
        return comps;
    }
};


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m, q;
    in >> n >> m >> q;

    vector<int> doru(m), dorv(m);
    for (int i = 0; i < m; i++)
        in >> doru[i] >> dorv[i];

    vector<int> razr(q);
    vector<bool> trogaem(m, false);
    for (int i = 0; i < q; i++) 
    {
        in >> razr[i];
        razr[i]--;
        trogaem[razr[i]] = true;
    }

    DSU D(n);
    for (int i = 0; i < m; i++) 
    {
        if (!trogaem[i])
            D.unite(doru[i] - 1, dorv[i] - 1);
    }

    vector<int> res(q);
    for (int i = q - 1; i >= 0; i--) 
    {
        res[i] = (D.getComps() == 1) ? 1 : 0;
        D.unite(doru[razr[i]] - 1, dorv[razr[i]] - 1);
    }

    for (int i = 0; i < q; i++)
    {
        out << res[i];
    }

    return 0;
}