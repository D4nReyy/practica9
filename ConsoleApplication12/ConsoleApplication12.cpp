#include <iostream>
#include <windows.h>

int NOD(int a, int b) 
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

struct ThreadData
{
    int a;
    int b;
    int result;
};  

DWORD WINAPI findNOD(LPVOID param) {
    ThreadData* data = (ThreadData*)param;
    data->result = NOD(data->a, data->b);
    return 0;
}

int main() 
{
    setlocale(LC_ALL, "rus");
    int num1, num2;
    std::cout << "Введите два числа: ";
    std::cin >> num1 >> num2;

    HANDLE threads[2];
    ThreadData data[2];
    data[0].a = num1;
    data[0].b = num2;
    data[1].a = num2;
    data[1].b = num1;

    for (int i = 0; i < 2; ++i) {
        threads[i] = CreateThread(NULL, 0, findNOD, &data[i], 0, NULL);
    }

    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    for (int i = 0; i < 2; ++i) {
        CloseHandle(threads[i]);
    }

    std::cout << "Наибольший общий делитель чисел " << num1 << " и " << num2 << " равен " << data[0].result << std::endl;

    return 0;
}