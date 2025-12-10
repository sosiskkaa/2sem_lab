#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
    int N, M;
    std::cout << "Enter maximum number of simultaneous downloads (N): ";
    std::cin >> N;
    std::cout << "Enter total number of files to download (M, must be > N): ";
    std::cin >> M;

    if (M <= N) {
        std::cout << "Error: M must be greater than N!\n";
        return 1;
    }

    // семафор для ограничения одновременных загрузок
    HANDLE hDownloadSlots = CreateSemaphoreA(
        NULL,
        N,              // начальное значение
        N,              // максимальное значение
        "DownloadSlots"
    );

    // мьютекс для защиты журнала
    HANDLE hLogMutex = CreateMutexA(
        NULL,
        FALSE,          // не владеть сразу
        "LogAccessMutex"
    );

    // событие для сигнала о закрытии
    HANDLE hBrowserClosingEvent = CreateEventA(
        NULL,
        TRUE,           // manual-reset event
        FALSE,          // начальное состояние - несигнальное
        "BrowserClosingEvent"
    );

    if (!hDownloadSlots || !hLogMutex || !hBrowserClosingEvent) {
        std::cout << "Error creating synchronization objects!\n";
        return 1;
    }

    std::cout << "\nCreated synchronization objects:\n";
    std::cout << "- Semaphore: DownloadSlots (max " << N << " slots)\n";
    std::cout << "- Mutex: LogAccessMutex\n";
    std::cout << "- Event: BrowserClosingEvent\n\n";

    std::vector<HANDLE> hProcesses;
    std::vector<PROCESS_INFORMATION> processInfos;

    for (int i = 1; i <= M; i++) {
        std::string filename = "file_" + std::to_string(i) + ".dat";
        std::string commandLine = "Downloader.exe " +
            std::to_string(i) + " " +
            filename;

        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        if (CreateProcessA(
            NULL,
            const_cast<char*>(commandLine.c_str()),
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi
        )) {
            hProcesses.push_back(pi.hProcess);
            processInfos.push_back(pi);
            std::cout << "Started downloader " << i <<
                " for file: " << filename << "\n";
        }
        else {
            std::cout << "Failed to start downloader " << i << "\n";
        }

        Sleep(100);
    }

    std::cout << "\n=== Browser is running ===" << std::endl;
    std::cout << "Started " << hProcesses.size() <<
        " downloader processes" << std::endl;
    std::cout << "Press Enter to close browser and stop all downloads...\n";

    std::cin.ignore();
    std::cin.get();

    std::cout << "\n=== Browser is closing ===" << std::endl;
    std::cout << "Sending termination signal to all downloads...\n";

    SetEvent(hBrowserClosingEvent);

    std::cout << "Waiting for all downloaders to finish...\n";

    if (!hProcesses.empty()) {
        WaitForMultipleObjects(
            static_cast<DWORD>(hProcesses.size()),
            hProcesses.data(),
            TRUE,
            INFINITE
        );
    }

    for (size_t i = 0; i < processInfos.size(); i++) {
        CloseHandle(processInfos[i].hThread);
        CloseHandle(processInfos[i].hProcess);
    }

    CloseHandle(hDownloadSlots);
    CloseHandle(hLogMutex);
    CloseHandle(hBrowserClosingEvent);

    std::cout << "\nAll downloaders finished. Browser closed.\n";
    return 0;
}