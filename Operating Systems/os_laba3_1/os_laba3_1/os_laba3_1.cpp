#include <windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

struct ThreadData 
{
    int threadNum;
    int arraySize;
    int* sharedArray;
    CRITICAL_SECTION* critSect;
    HANDLE eventPause;
    HANDLE eventContinue;
    HANDLE eventTerminate;
    HANDLE eventStart;
};

DWORD WINAPI MarkerThread(LPVOID param) 
{
    ThreadData* data = (ThreadData*)param;
    int threadNum = data->threadNum;
    int arraySize = data->arraySize;
    int* sharedArray = data->sharedArray;
    CRITICAL_SECTION* critSect = data->critSect;
    HANDLE eventPause = data->eventPause;
    HANDLE eventContinue = data->eventContinue;
    HANDLE eventTerminate = data->eventTerminate;
    HANDLE eventStart = data->eventStart;

    WaitForSingleObject(eventStart, INFINITE);

    srand(threadNum);

    int marksMade = 0;

    while (true) 
    {
        bool stalled = false;
        int blockedIndex = -1;

        while (true) 
        {
            int index = rand() % arraySize;

            EnterCriticalSection(critSect);
            if (sharedArray[index] == 0) 
            {
                LeaveCriticalSection(critSect);
                Sleep(5);
                EnterCriticalSection(critSect);

                if (sharedArray[index] == 0) 
                {
                    sharedArray[index] = threadNum;
                    marksMade++;
                    LeaveCriticalSection(critSect);
                    Sleep(5);
                }
                else 
                {
                    blockedIndex = index;
                    stalled = true;
                    LeaveCriticalSection(critSect);
                    break;
                }
            }
            else 
            {
                blockedIndex = index;
                stalled = true;
                LeaveCriticalSection(critSect);
                break;
            }
        }

        if (!stalled) 
        {
            continue;
        }

        cout << "Marker " << threadNum << " paused after making " << marksMade
            << " marks, blocked at index " << blockedIndex << endl;

        SetEvent(eventPause);

        HANDLE events[2] = { eventContinue, eventTerminate };
        DWORD waitResult = WaitForMultipleObjects(2, events, FALSE, INFINITE);

        if (waitResult == WAIT_OBJECT_0) 
        {
            ResetEvent(eventContinue);
            continue;
        }
        else 
        {
            EnterCriticalSection(critSect);
            for (int i = 0; i < arraySize; i++) 
            {
                if (sharedArray[i] == threadNum) 
                {
                    sharedArray[i] = 0;
                }
            }
            LeaveCriticalSection(critSect);

            cout << "Marker " << threadNum << " terminating and cleared its marks." << endl;
            return 0;
        }
    }

    return 0;
}

int main() 
{
    setlocale(LC_ALL, "ru");
    SetConsoleOutputCP(65001);
    int arraySize;
    cout << "Введите размер общего массива: ";
    cin >> arraySize;

    if (arraySize <= 0) 
    {
        cout << "Размер массива должен быть положительным числом." << endl;
        return 1;
    }

    int* sharedArray = new int[arraySize] {};
    int nThreads;
    cout << "Введите количество потоков marker: ";
    cin >> nThreads;

    if (nThreads <= 0) 
    {
        cout << "Количество потоков должно быть положительным числом." << endl;
        delete[] sharedArray;
        return 1;
    }

    CRITICAL_SECTION critSect;
    InitializeCriticalSection(&critSect);

    vector<HANDLE> eventPauseArray(nThreads);
    vector<HANDLE> eventTerminateArray(nThreads);
    HANDLE eventContinueAll = CreateEvent(NULL, TRUE, FALSE, NULL);
    HANDLE eventStartAll = CreateEvent(NULL, TRUE, FALSE, NULL);

    vector<HANDLE> threads(nThreads);
    vector<ThreadData> threadDataArray(nThreads);

    for (int i = 0; i < nThreads; i++) 
    {
        eventPauseArray[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        eventTerminateArray[i] = CreateEvent(NULL, TRUE, FALSE, FALSE);

        threadDataArray[i].threadNum = i + 1;
        threadDataArray[i].arraySize = arraySize;
        threadDataArray[i].sharedArray = sharedArray;
        threadDataArray[i].critSect = &critSect;
        threadDataArray[i].eventPause = eventPauseArray[i];
        threadDataArray[i].eventContinue = eventContinueAll;
        threadDataArray[i].eventTerminate = eventTerminateArray[i];
        threadDataArray[i].eventStart = eventStartAll;

        threads[i] = CreateThread(NULL, 0, MarkerThread, &threadDataArray[i], 0, NULL);
        if (threads[i] == NULL) 
        {
            cerr << "Ошибка создания потока " << (i + 1) << endl;
            return 1;
        }
    }

    SetEvent(eventStartAll);

    bool* activeThreads = new bool[nThreads];
    for (int i = 0; i < nThreads; i++) activeThreads[i] = true;

    int activeCount = nThreads;

    while (activeCount > 0) 
    {
        for (int i = 0; i < nThreads; i++) 
        {
            if (activeThreads[i]) {
                WaitForSingleObject(eventPauseArray[i], INFINITE);
            }
        }

        EnterCriticalSection(&critSect);
        cout << "Текущее состояние массива:" << endl;
        for (int i = 0; i < arraySize; i++) 
        {
            cout << sharedArray[i] << ' ';
        }
        cout << endl;
        LeaveCriticalSection(&critSect);

        int threadToTerminate;
        cout << "Введите номер потока marker для завершения (от 1 до " << nThreads << "): ";
        cin >> threadToTerminate;

        if (threadToTerminate < 1 || threadToTerminate > nThreads || !activeThreads[threadToTerminate - 1]) 
        {
            cout << "Некорректный номер потока или поток уже завершен." << endl;
            for (int i = 0; i < nThreads; i++) 
            {
                if (activeThreads[i]) 
                {
                    ResetEvent(eventPauseArray[i]);
                }
            }
            continue;
        }

        SetEvent(eventTerminateArray[threadToTerminate - 1]);

        WaitForSingleObject(threads[threadToTerminate - 1], INFINITE);

        activeThreads[threadToTerminate - 1] = false;
        activeCount--;

        EnterCriticalSection(&critSect);
        cout << "Состояние массива после очистки завершённого потока:" << endl;
        for (int i = 0; i < arraySize; i++) 
        {
            cout << sharedArray[i] << ' ';
        }
        cout << endl;
        LeaveCriticalSection(&critSect);

        ResetEvent(eventPauseArray[threadToTerminate - 1]);
        ResetEvent(eventTerminateArray[threadToTerminate - 1]);

        for (int i = 0; i < nThreads; i++) 
        {
            if (activeThreads[i]) 
            {
                ResetEvent(eventPauseArray[i]);
            }
        }

        ResetEvent(eventContinueAll);
        SetEvent(eventContinueAll);
    }

    for (int i = 0; i < nThreads; i++)
    {
        CloseHandle(threads[i]);
        CloseHandle(eventPauseArray[i]);
        CloseHandle(eventTerminateArray[i]);
    }
    CloseHandle(eventContinueAll);
    CloseHandle(eventStartAll);
    DeleteCriticalSection(&critSect);

    delete[] sharedArray;
    delete[] activeThreads;

    cout << "Все потоки marker завершены, программа завершена." << endl;

    return 0;
}
