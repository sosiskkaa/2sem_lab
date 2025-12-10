#pragma once
#include <windows.h>
#include <vector>

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

class MarkSys
{
public:
    MarkSys(int arraySize, int nThreads);
    ~MarkSys();

    void start();
    void waitForPause(int threadId);
    void waitForAllPaused();
    void terminateMarker(int threadId);
    void continueOthers();
    vector<int> getArrayState();
    void stopAll();

private:
    int arraySize;
    int nThreads;
    int* sharedArray;
    CRITICAL_SECTION critSect;

    std::vector<HANDLE> threads;
    std::vector<ThreadData> threadDataArray;
    std::vector<HANDLE> eventPauseArray;
    std::vector<HANDLE> eventTerminateArray;
    HANDLE eventContinueAll;
    HANDLE eventStartAll;
    std::vector<bool> activeThreads;

    static DWORD WINAPI MarkerThread(LPVOID param);
};
