#include <iostream>
#include <future>
#include <cmath>
#include <deque>

class A
{
public:
    std::deque<int> numbers;
    std::deque<std::packaged_task<int(int)>> tasks;
    std::deque<std::future<int>> futures;

    std::future<int> Work(std::packaged_task<int(int)> task, int numb)
    {
        std::future<int> f = task.get_future();
        std::thread t(std::move(task), numb);
        t.detach();
        return move(f);
    }
};

A a;

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

void bob()
{
    int numb;
    bool False = true;
    while (False)
    {
        std::cout << "Enter a number\nNegative to stop: ";
        std::cin >> numb;
        if (numb < 0)
            break;
        std::packaged_task<int(int)> task(countOfEasyNum);
        a.tasks.push_back(std::move(task));
        a.numbers.push_back(numb);
    }

    for (int i = 0; i < a.tasks.size(); i++)
        a.futures.push_back(a.Work(std::move(a.tasks[i]), a.numbers[i]));

    for (int i = 0; i < a.futures.size(); i++)
    {
        std::cout << "\nNumber: " << a.numbers[i] << std::endl;
        std::cout << "Result: " << a.futures[i].get() << std::endl;
    }
}

int main()
{
    bob();
    std::cout << std::endl;
    return 0;
}