#include <iostream>
#include <future>
#include <cmath>

double time;

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
    clock_t start = clock();
    int res = 0;
    for (int i = 0; i < numb; i++)
        if (checkForEasyNum(i))
            res++;

    time = (double)(clock() - start) / CLOCKS_PER_SEC;
    return res;
}

void async(int option)
{
    int numb;
    std::string type;
    std::future<int> f1;

    std::cout << "Enter a number: ";
    std::cin >> numb;
    std::cout << std::endl;

    if (option == 1)
        f1 = std::async(std::launch::async, countOfEasyNum, numb);
    else if (option == 2)
        f1 = std::async(std::launch::deferred, countOfEasyNum, numb);
    else
    {
        std::cout << "BRUH" << std::endl;
        return;
    }

    std::cout << "While calculations is running, you can check this out" << std::endl
              << "1. Square root of your number" << std::endl
              << "2. Sin of your number" << std::endl
              << "3. ln of your number" << std::endl
              << "Anything to skip and wait :D" << std::endl;
    std::string bob;
    std::cin >> bob;
    if (bob == "1")
        std::cout << "Square root of your number is: " << sqrt(numb) << std::endl;
    else if (bob == "2")
        std::cout << "Sin of your number is: " << sin(numb) << std::endl;
    else if (bob == "3")
        std::cout << "ln of your number is: " << log(numb) << std::endl;

    std::cout << std::endl
              << "Ok, waiting for calculations..." << std::endl;

    int res = f1.get();
    std::cout << std::endl
              << "Number of easy numbers: " << res << std::endl
              << "Time of calculations: " << a.time << " SEC" << std::endl;
}

int main()
{
    std::cout << "Choose option:" << std::endl
              << "1. Async" << std::endl
              << "2. Deffer async" << std::endl;
    std::string option = "";
    std::cin >> option;
    std::cout << std::endl;
    if (option == "1")
        async(1);
    else if (option == "2")
        async(2);
    else
        std::cout << "BRUH" << std::endl;

    std::cout << std::endl;
    return 0;
}
