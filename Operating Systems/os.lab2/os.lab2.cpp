#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ������� ��� ��������� ������
void ErrorExit(const char* message)
{
    cerr << message << endl;
    ExitProcess(1);
}

// ����� ������� - ��������� ������
void ChildProcess()
{
    int size;
    DWORD bytesRead;

    // ������ ������� ������� �� stdin
    if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), &size, sizeof(size), &bytesRead, NULL))
    {
        ErrorExit("Child: ReadFile size failed");
    }

    cout << "Child: Reading array of size " << size << endl;

    // ������ �������
    vector<int> array(size);
    if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), array.data(), size * sizeof(int), &bytesRead, NULL))
    {
        ErrorExit("Child: ReadFile array failed");
    }

    // ���������� ����� ������������� ���������
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] > 0)
        {
            sum += array[i];
        }
    }

    cout << "Child: Calculated sum of positive elements: " << sum << endl;

    // ������ ���������� � stdout
    DWORD bytesWritten;
    if (!WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), &sum, sizeof(sum), &bytesWritten, NULL))
    {
        ErrorExit("Child: WriteFile result failed");
    }

    cout << "Child: Result sent to parent process" << endl;
}

// ����� ��������
void ParentProcess()
{
    // �������� �������
    int size;
    cout << "Enter array size: ";
    cin >> size;

    vector<int> array(size);

    cout << "Choose input method (1 - manual, 2 - random): ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++)
        {
            cin >> array[i];
        }
    }
    else
    {
        srand(static_cast<unsigned>(time(NULL)));
        cout << "Generated array: ";
        for (int i = 0; i < size; i++)
        {
            array[i] = rand() % 100 - 50; // ����� �� -50 �� 49
            cout << array[i] << " ";
        }
        cout << endl;
    }

    // �������� �������
    HANDLE hChildStdoutRd, hChildStdoutWr;
    HANDLE hChildStdinRd, hChildStdinWr;
    SECURITY_ATTRIBUTES saAttr;

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // �������� ������ ��� stdout ��������� ��������
    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
    {
        ErrorExit("Stdout pipe creation failed");
    }

    // �������� ������ ��� stdin ��������� ��������
    if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0))
    {
        ErrorExit("Stdin pipe creation failed");
    }

    // ��������� �������� ��� �������� ��������
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = hChildStdoutWr;
    si.hStdOutput = hChildStdoutWr;
    si.hStdInput = hChildStdinRd;
    si.dwFlags |= STARTF_USESTDHANDLES;

    ZeroMemory(&pi, sizeof(pi));

    // �������� ��������� ������ ��� ��������� ��������
    string commandLine = "child_process.exe child";

    // �������������� string � LPTSTR
    vector<char> cmdLine(commandLine.begin(), commandLine.end());
    cmdLine.push_back('\0');

    // �������� ��������� ��������
    if (!CreateProcessA(
        NULL,
        cmdLine.data(),
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi))
    {
        ErrorExit("CreateProcess failed");
    }

    // ��������� �������� ����������� � ������������ ��������
    CloseHandle(hChildStdoutWr);
    CloseHandle(hChildStdinRd);

    // ������ ������ � �������� �������
    DWORD bytesWritten;

    // ������ ������� �������
    if (!WriteFile(hChildStdinWr, &size, sizeof(size), &bytesWritten, NULL))
    {
        ErrorExit("Parent: WriteFile size failed");
    }

    // ������ �������
    if (!WriteFile(hChildStdinWr, array.data(), size * sizeof(int), &bytesWritten, NULL))
    {
        ErrorExit("Parent: WriteFile array failed");
    }

    // ��������� ���������� ������, ����� �������� ������� ������� EOF
    CloseHandle(hChildStdinWr);

    // ������ ���������� �� ��������� ��������
    int result;
    DWORD bytesRead;
    if (!ReadFile(hChildStdoutRd, &result, sizeof(result), &bytesRead, NULL))
    {
        ErrorExit("Parent: ReadFile result failed");
    }

    cout << "Parent: Received result from child: " << result << endl;

    // �������� ���������� ��������� ��������
    WaitForSingleObject(pi.hProcess, INFINITE);

    // �������� ������������
    CloseHandle(hChildStdoutRd);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    cout << "Parent: Child process completed successfully" << endl;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && string(argv[1]) == "child")
    {
        ChildProcess();
    }
    else
    {
        ParentProcess();
    }

    return 0;
}