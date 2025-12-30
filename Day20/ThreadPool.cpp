#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
        // 创建工作线程
        workers.emplace_back([this]() {
            while (true) {
                // 用于存放任务
                std::function<void()> task;
                {
                    // 加锁任务队列
                    std::unique_lock<std::mutex> lock(queueMutex);
                    // 等待任务到来或停止信号
                    condition.wait(lock, [this]() { return stop.load() || !tasks.empty(); });
                    if (stop.load() && tasks.empty()) {
                        return; // 退出线程
                    }

                    // 获取任务
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                // 执行任务
                if (task) {
                    task();
                }
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop.store(true);
    condition.notify_all();
    for (std::thread &worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::enqueueTask(const std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}
