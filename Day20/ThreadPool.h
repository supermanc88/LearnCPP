#ifndef LEARNCPP_THREADPOOL_H
#define LEARNCPP_THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>

class ThreadPool {

public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    // 加入任务到队列
    void enqueueTask(const std::function<void()> task);

private:
    // 工作线程
    std::vector<std::thread> workers;
    // 任务队列
    std::queue<std::function<void()>> tasks;

    // 互斥锁和条件变量
    std::mutex queueMutex;
    std::condition_variable condition;
    // 停止标志
    std::atomic<bool> stop;
};


#endif //LEARNCPP_THREADPOOL_H