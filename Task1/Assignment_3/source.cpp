#include <algorithm>
#include <iostream>
#include <list>
#include <thread>
#include <Windows.h>

std::list<int> l;

void AddToList(int numb)
{
    for (int i = 0; i < 10; i++)
    {
        l.push_back(numb + i);
        std::cout << "Added: " << numb + i << std::endl;
    }
}

void ListContains(int numb)
{
    std::list<int>::iterator it;
    for (int i = 0; i < 10; i++)
    {
        it = find(l.begin(), l.end(), numb);
        if (it != l.end())
            std::cout << "Found: " << numb << std::endl;
        else
            std::cout << "Not found: " << numb << std::endl;
    }
}

int main()
{
    system("cls");
    int numb = 5;
    int check = 6;
    std::thread t1(AddToList, numb);
    std::thread t2(ListContains, check);

    t1.join();
    t2.join();

    std::cout << std::endl;
    system("pause");
    return 0;
}