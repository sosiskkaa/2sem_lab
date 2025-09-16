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

    int maxNegative = numeric_limits<int>::min();
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

int main() 
{
    setlocale(LC_ALL, "Russian");

    int size;
    cout << "������� ������ �������: ";
    cin >> size;

    if (size <= 0) 
    {
        cout << "������ ������� ������ ���� �������������!" << endl;
        return 1;
    }

    int* array = new int[size];
    char choice;

    cout << "������ ������ �������� �������? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') 
    {
        cout << "������� " << size << " ��������� �������:" << endl;
        for (int i = 0; i < size; i++) 
        {
            cin >> array[i];
        }
    }
    else 
    {
        srand(time(NULL));
        cout << "��������������� ������:" << endl;
        for (int i = 0; i < size; i++) 
        {
            array[i] = rand() % 200 - 100;
            cout << array[i] << " ";
        }
        cout << endl;
    }

    int sleepTime;
    cout << "������� ��������� ���������� ��� ���������/������� (��): ";
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
        cout << "������ �������� ������!" << endl;
        delete[] array;
        return 1;
    }

    cout << "����� ������. ID ������: " << threadID << endl;
    cout << "���������� ������: " << hThread << endl;

    cout << "��������������� ����� �� " << sleepTime << " ��..." << endl;
    SuspendThread(hThread);
    Sleep(sleepTime);

    cout << "����������� ������ ������..." << endl;
    ResumeThread(hThread);

    WaitForSingleObject(hThread, INFINITE);

    cout << "������������ ������������� �������: " << data.result << endl;

    CloseHandle(hThread);
    delete[] array;

    cout << "\n������������ CreateThread (����� � ����������� ���������):" << endl;

    HANDLE hThread2;
    DWORD threadID2;

    hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)workerThread, &data, CREATE_SUSPENDED, &threadID2);

    if (hThread2 == NULL) 
    {
        cout << "������ �������� ������� ������!" << endl;
        return 1;
    }

    cout << "����� ������ � ����������� ���������. ID: " << threadID2 << endl;

    Sleep(sleepTime);
    cout << "�������� �����..." << endl;
    ResumeThread(hThread2);

    WaitForSingleObject(hThread2, INFINITE);
    CloseHandle(hThread2);

    cout << "������ ��������� ���������." << endl;

    return 0;
}