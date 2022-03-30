#include <iostream>
#include <condition_variable>
#include <algorithm>

std::mutex m;
std::condition_variable cv;

int value = 0;

std::atomic_bool finished = false;
int value_lower_limit = 1;
int value_upper_limit = 5;
int total_cycles = 3;
int cycle_count = 0;

void func1()
{
    while (!finished)
    {
        std::unique_lock lock(m);
        cv.wait(lock, [] { return value <= value_lower_limit;});
        while (value < value_upper_limit)
        {
            value++;
            std::cout << "1: " << value << std::endl;
        }
        cv.notify_one();
    }
}

void func2()
{
    while (!finished)
    {
        std::unique_lock lock(m);
        cv.wait(lock, [] { return value >= value_upper_limit;});
        while (value > value_lower_limit)
        {
            value -= 1;
            std::cout << "2: " << value << std::endl;
        }
        cv.notify_one();
        cycle_count++;
        if (cycle_count >= total_cycles)
            finished = true;
    }
}

int main()
{
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();
    return 0;
}
