#include <iostream>
#include <mutex>


int main() {
    int ret = 0;

    std::mutex mtx;
    mtx.lock();
    std::cout << "Hello, World!" << std::endl;
    mtx.unlock();

    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Do something thread-safe." << std::endl;
    }
    std::cout << "Auto unlocked after lock_guard goes out of scope." << std::endl;

    mtx.lock();
    std::cout << "Goodbye, World!" << std::endl;
    mtx.unlock();



    return ret;
}