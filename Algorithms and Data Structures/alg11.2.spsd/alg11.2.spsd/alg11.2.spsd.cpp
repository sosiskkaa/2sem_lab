#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point() : x(0), y(0) {}
};

vector<vector<int>> lab;
vector<vector<int>> reslab;
vector<vector<bool>> occup;
vector<vector<Point>> parent;
int n, m, k;

int dx[8] = { 0, 1, 1,  1,  0, -1, -1, -1 };
int dy[8] = { 1, 1, 0, -1, -1, -1,  0,  1 };

bool DFS(int x, int y, int ex, vector<Point>& path, vector<vector<bool>>& visited, int ldir)
{
    if (occup[x][y] || visited[x][y]) 
        return false;
    visited[x][y] = true;
    path.push_back(Point(x, y));

    if (x == n - 1 && y == ex - 1) 
    {
        return true;
    }

    int sdir = (ldir + 2) % 8;

    for (int k = 0; k < 8; k++) 
    {
        int dir = (sdir + k) % 8;
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx >= 0 && nx < n && ny >= 0 && ny < m && lab[nx][ny] == 0 && !occup[nx][ny] && !visited[nx][ny])
        {
            if (DFS(nx, ny, ex, path, visited, dir))
            {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

bool dfs(int stx, int sty, int ex, vector<Point>& path)
{
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    path.clear();
    return DFS(stx, sty, ex, path, visited, 2);
}

int main()
{
    ifstream in("labyrinth.in");
    ofstream out("labyrinth.out");

    in >> n >> m >> k;

    vector<int> lin(k);
    vector<int> lout(k);

    for (int i = 0; i < k; i++) in >> lin[i];
    for (int i = 0; i < k; i++) in >> lout[i];

    lab.resize(n, vector<int>(m));
    reslab.resize(n, vector<int>(m));
    occup.assign(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            in >> lab[i][j];
            reslab[i][j] = lab[i][j];
            if (lab[i][j] == 1) occup[i][j] = true;
        }
    }

    vector<int> order(k);
    for (int i = 0; i < k; i++)
    {
        order[i] = i;
    }

    sort(order.begin(), order.end(), [&](int a, int b) {
        return abs(lout[a] - lin[a]) < abs(lout[b] - lin[b]);
        });

    int pcount = 0;

    for (int pind : order)
    {
        vector<Point> path;
        int start_x = 0;
        int start_y = lin[pind] - 1;

        if (dfs(start_x, start_y, lout[pind], path))
        {
            pcount++;
            for (const Point& p : path)
            {
                if (!(p.x == 0 || p.x == n - 1))
                {
                    occup[p.x][p.y] = true;
                }
                if (reslab[p.x][p.y] == 0)
                {
                    reslab[p.x][p.y] = pind + 2;
                }
            }
        }
    }

    out << pcount << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            out << reslab[i][j];
            if (j < m - 1) out << " ";
        }
        out << endl;
    }

    return 0;
}