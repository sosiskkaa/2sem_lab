#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "Shared.h"

int main()
{
    int N, M;
    std::cout << "Enter number of workers (N): ";
    std::cin >> N;
    std::cout << "Enter number of tasks (M): ";
    std::cin >> M;

    //Контейнеры для хранения дескрипторов каналов и информации о процессах
    std::vector<HANDLE> hPipesIn(N);  // Каналы для записи (Browser -> Worker)
    std::vector<HANDLE> hPipesOut(N); // Каналы для чтения (Worker -> Browser)
    std::vector<PROCESS_INFORMATION> pi(N); // Информация о запущенных процессах

    //Создание каналов и запуск процессов
    for (int i = 0; i < N; ++i)
    {
        //Формируем уникальные имена каналов по ID воркера
        std::wstring pipeInName = L"\\\\.\\pipe\\worker_in_" + std::to_wstring(i);
        std::wstring pipeOutName = L"\\\\.\\pipe\\worker_out_" + std::to_wstring(i);

        //именованный канал для отправки задач (Outbound)
        hPipesIn[i] = CreateNamedPipeW(
            pipeInName.c_str(), 
            PIPE_ACCESS_OUTBOUND,       // Направление: только от сервера к клиенту
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // Сообщения, блокирующий режим
            1, 1024, 1024, 0, NULL);

        //именованный канал для получения результатов (Inbound)
        hPipesOut[i] = CreateNamedPipeW(
            pipeOutName.c_str(), 
            PIPE_ACCESS_INBOUND,        //аправление: только от клиента к серверу
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 
            1, 1024, 1024, 0, NULL);

        //Подготовка к запуску дочернего процесса Worker.exe
        STARTUPINFOW si = { sizeof(si) };
        std::wstring cmd = L"Worker.exe " + std::to_wstring(i); //Передаем ID как аргумент

        if (!CreateProcessW(NULL, &cmd[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi[i]))
        {
            std::cerr << "Failed to launch worker " << i << std::endl;
            continue;
        }

        //Ожидание подключения воркера к созданным каналам
        ConnectNamedPipe(hPipesIn[i], NULL);
        ConnectNamedPipe(hPipesOut[i], NULL);
    }

    //Распределение задач
    for (int j = 0; j < M; ++j)
    {
        int workerIdx = j % N; //Выбираем воркера по очереди
        Task task = { TASK_PROCESS, { (float)j, (float)j + 5, (float)j + 10 } };
        DWORD written, read;
        Response res;

        //Отправляем задачу в канал worker_in
        WriteFile(hPipesIn[workerIdx], &task, sizeof(Task), &written, NULL);

        //Читаем результат из канала worker_out (блокирующая операция)
        if (ReadFile(hPipesOut[workerIdx], &res, sizeof(Response), &read, NULL))
        {
            std::cout << "[Browser] Task " << j << " processed by Worker " << workerIdx 
                      << ". Result (Sepia): " << res.result << std::endl;
        }
    }

    //Завершение работы
    for (int i = 0; i < N; ++i)
    {
        Task termTask = { TASK_TERMINATE, {0, 0, 0} };
        DWORD written;

        //Отправляем сигнал стоп
        WriteFile(hPipesIn[i], &termTask, sizeof(Task), &written, NULL);

        //пока процесс воркера закроется сам
        WaitForSingleObject(pi[i].hProcess, INFINITE);

        //чистка
        CloseHandle(hPipesIn[i]);
        CloseHandle(hPipesOut[i]);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}