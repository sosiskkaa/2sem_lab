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
    
    int size, zap;
    in >> size >> zap;

    DSU D(size);

    int u, v;
    for (int i = 0; i < zap; i++)
    {
        in >> u >> v;
        D.unite(u - 1, v - 1);
        out << D.getComps() << endl;
    }

    return 0;
}