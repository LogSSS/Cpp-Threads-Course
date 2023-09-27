#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

std::mutex m;

void Thread1()
{
    m.lock();
    std::cout << "1" << std::endl;
    m.unlock();
}

void Thread2()
{
    m.lock();
    std::cout << "2" << std::endl;
    m.unlock();
}

int main()
{
    system("cls");
    std::thread t1(Thread1);
    std::thread t2(Thread2);

    t1.detach();
    t2.detach();

    std::cout << std::endl;
    system("pause");
    return 0;
}
