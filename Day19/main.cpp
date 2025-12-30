#include <iostream>
#include <thread>


std::atomic<int> counter(0);

int main() {
    int ret = 0;
    std::cout << "Hello, Day 19!" << std::endl;

    std::thread t1([]() {
        for (int i = 0; i < 1000; ++i) {
            counter++;
        }
    });

    std::thread t2([]() {
        for (int i = 0; i < 1000; ++i) {
            counter++;
        }
    });

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter.load() << std::endl;



    return ret;
}