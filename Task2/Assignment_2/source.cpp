#include <algorithm>
#include <iostream>
#include <iomanip>
#include <list>
#include <mutex>
#include <thread>
#include <Windows.h>

class someDate;
class exchangePerson;

class someDate
{
public:
    std::string name;
    std::string surname;
    std::string address;
    int age;

    void print(int i)
    {
        std::string per = "Person " + std::to_string(i);
        std::cout << std::left << std::setw(10) << per
                  << std::setw(10) << this->name
                  << std::setw(10) << this->surname
                  << std::setw(10) << this->address
                  << std::setw(10) << this->age << std::endl;
    }
};

class exchangePerson
{
public:
    someDate data;
    std::mutex m;

    static void JohnDoe(exchangePerson &person)
    {
        std::lock_guard<std::mutex> lock(person.m);
        person.data.name = "John";
        person.data.surname = "Doe";
        person.data.address = "Unknown";
        person.data.age = 120;
    }

    static void JacobSmith(exchangePerson &person)
    {
        std::lock_guard<std::mutex> lock(person.m);
        person.data.name = "Jacob";
        person.data.surname = "Smith";
        person.data.address = "Known";
        person.data.age = 1;
    }

    static void Swap(exchangePerson &person1, exchangePerson &person2)
    {
        if (&person1 == &person2)
        {
            std::cout << "Cant swap, same person" << std::endl;
            return;
        }

        std::lock_guard<std::mutex> lock1(person1.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(person2.m, std::adopt_lock);
        std::lock(person1.m, person2.m);
        printHeader("Before swap");
        person1.data.print(1);
        person2.data.print(2);
        exchangePerson temp;
        temp.data = person1.data;
        person1.data = person2.data;
        person2.data = temp.data;
        printHeader("After swap");
        person1.data.print(1);
        person2.data.print(2);
    }

    static void printHeader(std::string str)
    {
        std::cout << std::setfill('-') << std::setw(60) << "-"
                  << std::endl
                  << str << std::endl
                  << std::endl
                  << std::setfill(' ') << std::left << std::setw(10) << "Field"
                  << std::setw(10) << "Name"
                  << std::setw(10) << "Surname"
                  << std::setw(10) << "Address"
                  << std::setw(10) << "Age" << std::endl;
    }
};

int main()
{
    system("cls");

    exchangePerson John, Jacob;

    std::thread thread1(exchangePerson::JohnDoe, std::ref(John));
    thread1.detach();

    std::thread thread2(exchangePerson::JacobSmith, std::ref(Jacob));
    thread2.detach();

    std::thread swap(exchangePerson::Swap, std::ref(John), std::ref(Jacob));
    swap.join();

    system("pause");
    return 0;
}
