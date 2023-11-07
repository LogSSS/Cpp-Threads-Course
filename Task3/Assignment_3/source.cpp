#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "windows.h"

std::condition_variable notif;
std::mutex m;
int i = 0;
int sleepTime = 100;

void Notify()
{
    std::unique_lock<std::mutex> lock(m);
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    lock.lock();
    std::cout << "Notify one" << std::endl
              << std::endl;
    i = 1;
    notif.notify_one();
}

void Waits(int id)
{
    std::unique_lock<std::mutex> lock(m);
    notif.wait(lock, []
               { return i; });
    std::cout << "Status: " << id << " is notified" << std::endl;
}

int main()
{

    std::thread w1(Waits, 1);
    w1.detach();
    std::thread w2(Waits, 2);
    w2.detach();
    std::thread w3(Waits, 3);
    w3.detach();

    std::thread notify(Notify);
    notify.join();

    Sleep(100);

    std::cout << std::endl;
    return 0;
}
