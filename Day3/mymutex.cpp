#include <iostream>

class LockGuard {
private:
    std::mutex& m;
public:
    LockGuard(std::mutex& m_) : m(m_) {
        m.lock();
        std::cout << "mutex locked" << std::endl;
    }
    ~LockGuard() {
        m.unlock();
        std::cout << "mutex unlocked" << std::endl;
    }
};

int main() {
    std::mutex mtx;
    {
        LockGuard lock(mtx);
        // Critical section
    } // mtx is automatically unlocked here

    std::cout << "auto mutex unlock in the previous scope" << std::endl;
    return 0;
}


