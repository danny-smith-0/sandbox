#include <iostream>
#include <condition_variable>
#include <algorithm>

std::mutex m;
std::condition_variable cv;
int value = 0;
int count = 0;

void func1()
{
    std::unique_lock lock(m);
    cv.wait(lock, [] { return value < 1;});
    value++;
    std::cout << "1: " << value << std::endl;
    cv.notify_one();
}

void func2()
{
    std::unique_lock lock(m);
    cv.wait(lock, [] { return value > 100;});
    value -= 100;
    std::cout << "2: " << value << std::endl;
    count++;
    cv.notify_one();
    if (count >= 5)
        int abc = 1;
}

int main()
{
    std::thread t1(func1);
    std::thread t2(func2);
    return 0;
}
