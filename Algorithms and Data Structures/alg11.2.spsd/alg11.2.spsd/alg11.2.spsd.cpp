#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point() : x(0), y(0) {}
};

vector<vector<int>> lab;
vector<vector<int>> reslab;
vector<vector<bool>> occup;
vector<vector<Point>> parent;
int n, m, k;

bool bfs(int stx, int sty, int ex, vector<Point>& path) 
{
    if (occup[stx][sty])
        return false;

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    parent.assign(n, vector<Point>(m, Point(-1, -1)));

    queue<Point> q;
    q.push(Point(stx, sty));
    visited[stx][sty] = true;

    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    while (!q.empty()) 
    {
        Point current = q.front();
        q.pop();

        int i = current.x, j = current.y;

        if (i == n - 1 && j == ex - 1) 
        {
            path.clear();
            Point node = current;
            while (node.x != -1 && node.y != -1) 
            {
                path.push_back(node);
                node = parent[node.x][node.y];
            }
            reverse(path.begin(), path.end());
            return true;
        }

        for (int dir = 0; dir < 8; dir++) 
        {
            int ni = i + dx[dir];
            int nj = j + dy[dir];

            if (ni >= 0 && ni < n && nj >= 0 && nj < m && !visited[ni][nj] && !occup[ni][nj] && lab[ni][nj] == 0) 
            {
                visited[ni][nj] = true;
                parent[ni][nj] = current;
                q.push(Point(ni, nj));
            }
        }
    }

    return false;
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

        if (bfs(start_x, start_y, lout[pind], path)) 
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
