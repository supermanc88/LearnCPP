#include <iostream>

void test() {
    std::cout << "test function" << std::endl;
}


int main() {
    int ret = 0;
    std::cout << "funtion object test" << std::endl;

    // std::function<返回类型(参数列表)>

    std::function<void()> f;

    f = []() {
        std::cout << "Hello, World!" << std::endl;
    };

    f();

    f = test;
    f();


    return ret;
}