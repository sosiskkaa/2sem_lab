#include "pch.h"
#include "MarkSys.h"
#include <iostream>

MarkSys::MarkSys(int arraySize, int nThreads)
    : arraySize(arraySize), nThreads(nThreads)
{
    sharedArray = new int[arraySize] {};
    InitializeCriticalSection(&critSect);

    eventPauseArray.resize(nThreads);
    eventTerminateArray.resize(nThreads);
    threads.resize(nThreads);
    threadDataArray.resize(nThreads);
    activeThreads.resize(nThreads, true);

    eventContinueAll = CreateEvent(NULL, TRUE, FALSE, NULL);
    eventStartAll = CreateEvent(NULL, TRUE, FALSE, NULL);

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
    }
}

MarkSys::~MarkSys()
{
    stopAll();
    delete[] sharedArray;
    DeleteCriticalSection(&critSect);
}

void MarkSys::start()
{
    SetEvent(eventStartAll);
}

void MarkSys::waitForPause(int threadId)
{
    WaitForSingleObject(eventPauseArray[threadId - 1], INFINITE);
}

void MarkSys::waitForAllPaused()
{
    for (int i = 0; i < nThreads; i++)
        if (activeThreads[i])
            WaitForSingleObject(eventPauseArray[i], INFINITE);
}

void MarkSys::terminateMarker(int threadId)
{
    SetEvent(eventTerminateArray[threadId - 1]);
    WaitForSingleObject(threads[threadId - 1], INFINITE);
    activeThreads[threadId - 1] = false;
}

void MarkSys::continueOthers()
{
    ResetEvent(eventContinueAll);
    SetEvent(eventContinueAll);
}

vector<int> MarkSys::getArrayState()
{
    vector<int> result(arraySize);
    EnterCriticalSection(&critSect);
    for (int i = 0; i < arraySize; i++)
        result[i] = sharedArray[i];
    LeaveCriticalSection(&critSect);
    return result;
}

void MarkSys::stopAll()
{
    for (int i = 0; i < nThreads; i++)
    {
        if (threads[i])
        {
            CloseHandle(threads[i]);
            CloseHandle(eventPauseArray[i]);
            CloseHandle(eventTerminateArray[i]);
        }
    }
    CloseHandle(eventContinueAll);
    CloseHandle(eventStartAll);
}

DWORD WINAPI MarkSys::MarkerThread(LPVOID param)
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
            continue;

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
                if (sharedArray[i] == threadNum)
                    sharedArray[i] = 0;
            LeaveCriticalSection(critSect);
            return 0;
        }
    }
    return 0;
}
