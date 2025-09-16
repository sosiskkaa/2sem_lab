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
    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) 
    {
        cout << "Размер массива должен быть положительным!" << endl;
        return 1;
    }

    int* array = new int[size];
    char choice;

    cout << "Хотите ввести элементы вручную? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') 
    {
        cout << "Введите " << size << " элементов массива:" << endl;
        for (int i = 0; i < size; i++) 
        {
            cin >> array[i];
        }
    }
    else 
    {
        srand(time(NULL));
        cout << "Сгенерированный массив:" << endl;
        for (int i = 0; i < size; i++) 
        {
            array[i] = rand() % 200 - 100;
            cout << array[i] << " ";
        }
        cout << endl;
    }

    int sleepTime;
    cout << "Введите временной промежуток для остановки/запуска (мс): ";
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
        cout << "Ошибка создания потока!" << endl;
        delete[] array;
        return 1;
    }

    cout << "Поток создан. ID потока: " << threadID << endl;
    cout << "Дескриптор потока: " << hThread << endl;

    cout << "Приостанавливаю поток на " << sleepTime << " мс..." << endl;
    SuspendThread(hThread);
    Sleep(sleepTime);

    cout << "Возобновляю работу потока..." << endl;
    ResumeThread(hThread);

    WaitForSingleObject(hThread, INFINITE);

    cout << "Максимальный отрицательный элемент: " << data.result << endl;

    CloseHandle(hThread);
    delete[] array;

    cout << "\nДемонстрация CreateThread (поток в подвешенном состоянии):" << endl;

    HANDLE hThread2;
    DWORD threadID2;

    hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)workerThread, &data, CREATE_SUSPENDED, &threadID2);

    if (hThread2 == NULL) 
    {
        cout << "Ошибка создания второго потока!" << endl;
        return 1;
    }

    cout << "Поток создан в подвешенном состоянии. ID: " << threadID2 << endl;

    Sleep(sleepTime);
    cout << "Запускаю поток..." << endl;
    ResumeThread(hThread2);

    WaitForSingleObject(hThread2, INFINITE);
    CloseHandle(hThread2);

    cout << "Работа программы завершена." << endl;

    return 0;
}