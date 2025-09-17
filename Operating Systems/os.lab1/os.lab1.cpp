#include <windows.h>
#include <process.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct ThreadData
{
    int* array;
    int size;
    int sleepTime;
    int result;
};

unsigned __stdcall workerThread(void* param)
{
    ThreadData* data = (ThreadData*)param;

    int maxNegative = (numeric_limits<int>::min)();
    bool found = false;

    for (int i = 0; i < data->size; i++)
    {
        if (data->array[i] < 0)
        {
            if (!found || data->array[i] > maxNegative)
            {
                maxNegative = data->array[i];
                found = true;
            }
        }
    }

    data->result = found ? maxNegative : 0;

    Sleep(100);

    return 0;
}

DWORD WINAPI workerThreadCreateThread(LPVOID param)
{
    return workerThread(param);
}

int main()
{
    int size;
    cout << "Enter array size: ";
    cin >> size;

    if (size <= 0)
    {
        cout << "Array size must be positive!" << endl;
        return 1;
    }

    int* array = new int[size];
    char choice;

    cout << "Enter elements manually? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter " << size << " array elements:" << endl;
        for (int i = 0; i < size; i++)
        {
            cin >> array[i];
        }
    }
    else
    {
        srand(time(NULL));
        cout << "Generated array:" << endl;
        for (int i = 0; i < size; i++)
        {
            array[i] = rand() % 200 - 100;
            cout << array[i] << " ";
        }
        cout << endl;
    }

    int sleepTime;
    cout << "Enter pause/resume interval (ms): ";
    cin >> sleepTime;

    ThreadData data;
    data.array = array;
    data.size = size;
    data.sleepTime = sleepTime;
    data.result = 0;

    HANDLE hThread;
    unsigned threadID;

    hThread = (HANDLE)_beginthreadex(NULL, 0, workerThread, &data, 0, &threadID);

    if (hThread == NULL)
    {
        cout << "Thread creation error!" << endl;
        delete[] array;
        return 1;
    }

    SuspendThread(hThread);
    Sleep(sleepTime);

    ResumeThread(hThread);

    WaitForSingleObject(hThread, INFINITE);

    cout << "maximum negative element: " << data.result << endl;

    CloseHandle(hThread);

    delete[] array;

    return 0;
}