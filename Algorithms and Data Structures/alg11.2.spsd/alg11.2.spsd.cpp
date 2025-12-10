#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

struct Point
{
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point() : x(0), y(0) {}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("labyrinth.in");
    ofstream out("labyrinth.out");

    if (!in.is_open()) return 0;

    int n, m, k;

    int dx[] = { 0, -1, -1, -1,  0,  1, 1, 1 };
    int dy[] = { 1,  1,  0, -1, -1, -1, 0, 1 };

    in >> n >> m >> k;

    vector<int> lin(k);
    vector<int> lout(k);
    vector<vector<int>> lab(n, vector<int>(m));

    for (int i = 0; i < k; i++)
    {
        in >> lin[i];
        lin[i]--;
    }
    for (int i = 0; i < k; i++)
    {
        in >> lout[i];
        lout[i]--;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            in >> lab[i][j];
        }
    }

    vector<vector<int>> isExit(n, vector<int>(m, 0));
    for (int i = 0; i < k; i++)
    {
        if (lout[i] >= 0 && lout[i] < m && lab[n - 1][lout[i]] == 0)
            isExit[n - 1][lout[i]] = 1;
    }

    int pcount = 0;

    for (int pind = 0; pind < k; pind++)
    {
        stack<pair<Point, int>> st;
        if (lab[0][lin[pind]] != 0)
            continue;

        st.push({ Point(0, lin[pind]), 6 });

        while (!st.empty())
        {
            Point current = st.top().first;
            int fr = st.top().second;
            st.pop();

            if (isExit[current.x][current.y] > 0)
            {
                isExit[current.x][current.y] = pind + 2;
                pcount++;
                break;
            }
            else
            {
                lab[current.x][current.y] = pind + 2;
            }

            int dir;
            bool fnxt = false;
            for (int t = 0; t < 8; t++)
            {
                dir = (fr + 1 + t) & 7;
                int ni = current.x + dx[dir];
                int nj = current.y + dy[dir];

                if (ni >= 0 && ni < n && nj >= 0 && nj < m && lab[ni][nj] == 0)
                {
                    st.push({ current, fr });
                    st.push({ Point(ni, nj), dir });
                    fnxt = true;
                    break;
                }
            }
            if (!fnxt)
            {
                if (!(current.x == n - 1 && isExit[current.x][current.y] > 0))
                    lab[current.x][current.y] = -1;
            }
        }

    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (lab[i][j] == -1)
            {
                lab[i][j] = 0;
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        if (lab[n - 1][j] == -1)
        {
            lab[n - 1][j] = 0;
        }
        if (isExit[n - 1][j] > 1)
        {
            lab[n - 1][j] = isExit[n - 1][j];
        }
    }

    out << pcount << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            out << lab[i][j];
            if (j < m - 1) out << " ";
        }
        out << '\n';
    }

    return 0;
}