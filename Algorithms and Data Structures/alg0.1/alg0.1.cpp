#include <iostream>

using namespace std;

int binSearch(int* M, int n, int key)
{
    int right = n;
    int left = 0;
    int mid;

    while(left < right)
    {
        mid = (right + left) / 2;

        if (M[mid] < key)
        {
            left = mid + 1;
        }
        else if (M[mid] > key)
        {
            right = mid;
        }
        else
            return mid;
    }
    return -1;
}

int bolRavSearch(int* M, int n, int key)
{
    int right = n;
    int left = 0;
    int mid;

    while (left < right)
    {
        mid = (right + left) / 2;

        if (M[mid] < key)
        {
            left = mid + 1;
        }
        else
            right = mid;
    }
    return left;
}

int bolSearch(int* M, int n, int key)
{
    int right = n;
    int left = 0;
    int mid;

    while (left < right)
    {
        mid = (right + left) / 2;

        if (M[mid] <= key)
        {
            left = mid + 1;
        }
        else
            right = mid;
    }
    return left;
}

int main()
{
    int n, z;
    
    cin >> n;
    int* M = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> M[i];
    }

    cin >> z;
    int* Zap = new int[z];

    for (int i = 0; i < z; i++)
    {
        cin >> Zap[i];
    }

    for (int i = 0; i < z; i++)
    {
        int b = binSearch(M, n, Zap[i]);
        if (b == -1)
            b = 0;
        else
            b = 1;
        int l = bolRavSearch(M, n, Zap[i]);
        int r = bolSearch(M, n, Zap[i]);

        cout << b << " " << l << " " << r << "\n";
    }

    delete[] M;
    delete[] Zap;
    return 0;
}