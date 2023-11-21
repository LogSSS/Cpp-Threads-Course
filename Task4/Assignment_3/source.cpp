#include <iostream>
#include <future>
#include <cmath>
#include <windows.h>

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

int countOfEasyNum(int numb)
{
    int res = 0;
    for (int i = 0; i < numb; i++)
        if (checkForEasyNum(i))
            res++;

    return res;
}

void first(int n, std::promise<int> promise1, std::promise<int> promise2, std::promise<bool> promise3)
{
    promise1.set_value(countOfEasyNum(n));
    std::cout << "Set TRUE" << std::endl;
    promise3.set_value(true);
    promise2.set_value(countOfEasyNum(n * 10));
}

void second(int n, std::future<bool> future3)
{
    bool flag = future3.get();
    std::cout << "FLAGY: " << flag << std::endl;
    Sleep(2000);
    std::cout << "sqrt(" << n << ") = " << sqrt(n) << std::endl;
}

int main()
{

    int numb;
    std::cout << "Enter a number: ";
    std::cin >> numb;
    std::promise<int> promise1;
    std::promise<int> promise2;
    std::promise<bool> promise3;

    std::future<int> future1 = promise1.get_future();
    std::future<int> future2 = promise2.get_future();
    std::future<bool> future3 = promise3.get_future();

    std::thread t1(first, numb, std::move(promise1), std::move(promise2), std::move(promise3));
    t1.detach();
    std::thread t2(second, numb, std::move(future3));
    t2.detach();

    int val1 = future1.get();
    int val2 = future2.get();
    std::cout << "Count of prime numbers before 'n': " << val1 << std::endl;
    std::cout << "Count of prime numbers before 'n * 10': " << val2 << std::endl;

    std::cout << std::endl;
    return 0;
}