#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <Windows.h>

std::mutex m;
std::list<int> l;

void AddToList(int numb)
{
    std::lock_guard<std::mutex> guard(m);
    l.push_back(numb);
    std::cout << "Added: " << numb << std::endl;
}

void ListContains(int numb)
{
    std::lock_guard<std::mutex> guard(m);
    if (find(l.begin(), l.end(), numb) != l.end())
        std::cout << "Found: " << numb << std::endl;
    else
        std::cout << "Not found: " << numb << std::endl;
}

int main()
{
    system("cls");

    int numb = 5;
    int check = 12;

    for (int i = 0; i < 10; ++i)
    {
        std::thread t1(AddToList, numb + i);
        std::thread t2(ListContains, check);

        t1.join();
        t2.join();
    }

    std::cout << std::endl;
    system("pause");
    return 0;
}
