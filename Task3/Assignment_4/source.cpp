#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "windows.h"

std::queue<int> q;
std::condition_variable notif;
std::mutex m;

void DataPreparation()
{
    std::cout << "Input count of numbers: ";
    int count;
    std::cin >> count;

    for (int i = 0; i < count; i++)
    {
        std::unique_lock<std::mutex> lock(m);
        std::cout << "Input number: ";
        int number;
        std::cin >> number;
        q.push(number);
    }
    notif.notify_all();
}

bool checkForEasyNum(int numb)
{
    if (numb <= 1)
        return false;
    if (numb <= 3)
        return true;
    if (numb % 2 == 0 || numb % 3 == 0)
        return false;

    for (int i = 5; i * i <= numb; i += 6)
        if (numb % i == 0 || numb % (i + 2) == 0)
            return false;

    return true;
}

void DataProcessing()
{
    std::unique_lock<std::mutex> lock(m);

    notif.wait(lock, []
               { return !q.empty(); });

    std::queue<int> tempQ = q;

    while (!tempQ.empty())
    {
        int temp = tempQ.front();
        if (checkForEasyNum(temp))
            std::cout << "Simple:" << temp << std::endl;
        tempQ.pop();
    }
}

int main()
{
    std::thread prepare(DataPreparation);
    prepare.detach();
    std::thread DO(DataProcessing);
    DO.join();

    Sleep(100);

    std::cout << std::endl;
    return 0;
}
