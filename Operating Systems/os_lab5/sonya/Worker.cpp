#include <windows.h>
#include <iostream>
#include <string>
#include "Shared.h"

int main(int argc, char* argv[])
{
    //наличия аргумента ID
    if (argc < 2) 
    {
        return 1;
    }

    std::string id = argv[1];
    
    //ормируем имена тех же каналов, что создал Browser
    std::wstring pipeInName = L"\\\\.\\pipe\\worker_in_" + std::wstring(id.begin(), id.end());
    std::wstring pipeOutName = L"\\\\.\\pipe\\worker_out_" + std::wstring(id.begin(), id.end());

    //одключаемся к каналу для чтения (со стороны воркера это GENERIC_READ)
    HANDLE hPipeIn = CreateFileW(pipeInName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    
    //одключаемся к каналу для записи (со стороны воркера это GENERIC_WRITE)
    HANDLE hPipeOut = CreateFileW(pipeOutName.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    //oсновной цикл обработки сообщений
    while (true)
    {
        Task task;
        DWORD read, written;

        //Пытаемся прочитать структуру задачи из входного канала
        if (ReadFile(hPipeIn, &task, sizeof(Task), &read, NULL) && read > 0)
        {
            // Если пришла команда на выход — прерываем цикл
            if (task.type == TASK_TERMINATE)
            {
                break;
            }

            Response res;
            res.result = (task.data.r * 0.393f) + (task.data.g * 0.769f) + (task.data.b * 0.189f);

            //задержка для имитации нагрузки на CPU
            Sleep(50); 

            //результат обратно в Browser
            WriteFile(hPipeOut, &res, sizeof(Response), &written, NULL);
        }
        else
        {
            break;
        }
    }

    //Закрываем дескрипторы перед выходом
    CloseHandle(hPipeIn);
    CloseHandle(hPipeOut);
    
    return 0;
}