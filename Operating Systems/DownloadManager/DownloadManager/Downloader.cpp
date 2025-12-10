#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void reverseBytes(BYTE* buffer, size_t size) {
    for (size_t i = 0; i < size / 2; i++) {
        std::swap(buffer[i], buffer[size - 1 - i]);
    }
}

int main(int argc, char* argv[]) {
    // получение параметров командной строки
    int downloaderId = (argc > 1) ? std::atoi(argv[1]) : 1;
    std::string filename = (argc > 2) ? argv[2] : "default_file.dat";

    // открытие объектов синхронизации
    HANDLE hDownloadSlots = OpenSemaphoreA(
        SEMAPHORE_ALL_ACCESS,
        FALSE,
        "DownloadSlots"
    );

    HANDLE hLogMutex = OpenMutexA(
        MUTEX_ALL_ACCESS,
        FALSE,
        "LogAccessMutex"
    );

    HANDLE hBrowserClosingEvent = OpenEventA(
        EVENT_ALL_ACCESS,
        FALSE,
        "BrowserClosingEvent"
    );

    if (!hDownloadSlots || !hLogMutex || !hBrowserClosingEvent) {
        std::cout << "[PID: " << GetCurrentProcessId()
            << "] Error: Failed to open synchronization objects!\n";
        return 1;
    }

    // ожидание слота или сигнала закрытия
    bool slotAcquired = false;
    HANDLE waitHandles[2] = { hDownloadSlots, hBrowserClosingEvent };

    DWORD waitResult = WaitForMultipleObjects(
        2,
        waitHandles,
        FALSE,
        INFINITE
    );

    // обработка результатов ожидания
    if (waitResult == WAIT_OBJECT_0) {
        slotAcquired = true;
    }
    else if (waitResult == WAIT_OBJECT_0 + 1) {
        WaitForSingleObject(hLogMutex, INFINITE);
        std::cout << "[PID: " << GetCurrentProcessId()
            << "] Download interrupted: Browser is closing.\n";
        ReleaseMutex(hLogMutex);

        CloseHandle(hDownloadSlots);
        CloseHandle(hLogMutex);
        CloseHandle(hBrowserClosingEvent);
        return 0;
    }
    else {
        WaitForSingleObject(hLogMutex, INFINITE);
        std::cout << "[PID: " << GetCurrentProcessId()
            << "] Error waiting for download slot (code: "
            << waitResult << ")\n";
        ReleaseMutex(hLogMutex);

        CloseHandle(hDownloadSlots);
        CloseHandle(hLogMutex);
        CloseHandle(hBrowserClosingEvent);
        return 1;
    }

    if (slotAcquired) {
        WaitForSingleObject(hLogMutex, INFINITE);
        std::cout << "[PID: " << GetCurrentProcessId()
            << "] Connection established. Starting download of '"
            << filename << "'...\n";
        ReleaseMutex(hLogMutex);

        srand(GetCurrentProcessId() + GetTickCount());
        int downloadTime = 1000 + (rand() % 2001);
        Sleep(downloadTime);

        const size_t BUFFER_SIZE = 2048;
        std::vector<BYTE> buffer(BUFFER_SIZE);

        // заполнение буфера тестовыми данными
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = static_cast<BYTE>(i % 256);
        }

        std::vector<BYTE> originalBuffer = buffer;
        reverseBytes(buffer.data(), BUFFER_SIZE);

        // проверка корректности обработки
        bool processingSuccessful = (buffer[0] == originalBuffer[BUFFER_SIZE - 1]) &&
            (buffer[BUFFER_SIZE - 1] == originalBuffer[0]);

        WaitForSingleObject(hLogMutex, INFINITE);
        std::cout << "[PID: " << GetCurrentProcessId()
            << "] File '" << filename << "' processed successfully.";

        if (processingSuccessful) {
            std::cout << " Byte order reversed correctly.";
        }
        std::cout << "\n";
        ReleaseMutex(hLogMutex);

        if (!ReleaseSemaphore(hDownloadSlots, 1, NULL)) {
            WaitForSingleObject(hLogMutex, INFINITE);
            std::cout << "[PID: " << GetCurrentProcessId()
                << "] Error releasing download slot!\n";
            ReleaseMutex(hLogMutex);
        }
    }

    if (WaitForSingleObject(hBrowserClosingEvent, 0) == WAIT_OBJECT_0) {
        WaitForSingleObject(hLogMutex, INFINITE);
        std::cout << "[PID: " << GetCurrentProcessId()
            << "] Download terminated by user.\n";
        ReleaseMutex(hLogMutex);
    }

    CloseHandle(hDownloadSlots);
    CloseHandle(hLogMutex);
    CloseHandle(hBrowserClosingEvent);

    return 0;
}