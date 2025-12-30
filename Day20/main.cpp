#include <iostream>
#include <thread>

#include "ThreadPool.h"

int test_thread_pool() {
    int ret = 0;

    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.enqueueTask([i]() {
            std::cout << "Task " << i << " is being processed by thread "
                      << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }



    return ret;
}


int main() {
    int ret = 0;

    test_thread_pool();


    return ret;
}