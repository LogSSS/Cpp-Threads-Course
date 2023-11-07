#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "windows.h"

std::condition_variable notif;
std::mutex m;
int i = 0;
int sleepTime = 100;

void Awake()
{
    std::unique_lock<std::mutex> lock(m);
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    lock.lock();
    std::cout << std::endl
              << "Notify all when i = 0" << std::endl
              << std::endl;
    notif.notify_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    std::cout << "Notify all again when i = 1" << std::endl
              << std::endl;
    i = 1;
    notif.notify_all();
}

void Waits()
{
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Status: waiting for i = 1" << std::endl;
    notif.wait(lock, []
               { return i; });
    std::cout << "Status: done" << std::endl;
}

int main()
{

    std::thread w1(Waits);
    w1.detach();
    std::thread w2(Waits);
    w2.detach();
    std::thread w3(Waits);
    w3.detach();

    std::thread awake(Awake);
    awake.join();

    Sleep(100);

    std::cout << std::endl;
    return 0;
}
