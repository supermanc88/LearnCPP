#include <iostream>
#include <thread>
#include <condition_variable>


std::mutex mutex;
std::condition_variable cond_var;
bool ready = false;

void thread_function1() {
    std::cout << "Hello from thread!" << std::endl;
    {
        std::lock_guard<std::mutex> lock(mutex);
        ready = true;
    }
    cond_var.notify_one();
}

void thread_function2() {
    std::cout << "Hello from another thread!" << std::endl;
    std::unique_lock<std::mutex> lock(mutex);
    cond_var.wait(lock, [] { return ready; });
    std::cout << "Thread 2 detected that thread 1 is ready!" << std::endl;
}


int main() {
    int ret = 0;

    std::thread t1(thread_function1);
    std::thread t2(thread_function2);


    t1.join();
    t2.join();

    return ret;
}