#include <thread>
#include <chrono>
#include <string>
#include <iostream>

void task1(std::string str)
{
    std::cout << str;
}

int main()
{
    std::thread t1(task1, "hello");
    t1.join();
}