#include <iostream>

// lambda test

int main() {
    int ret = 0;
    std::cout << "Lambda Test" << std::endl;

    // 1. Basic lambda
    auto add = [](int a, int b) { return a + b; };
    auto sum = add(3, 4);
    std::cout << "Sum of 3 and 4 is: " << sum << std::endl;

    // 2. Capturing variables by value
    int x = 10;
    auto multiplyByX = [x](int y) { return x * y; };
    std::cout << "10 multiplied by 5 is: " << multiplyByX(5) << std::endl;

    // 2.1 Dynamic capture value
    std::srand(std::time(nullptr));
    int a = std::rand() % 100;
    auto printA = [a]() { std::cout << "Captured value a is: " << a << std::endl; };
    printA();

    a = std::rand() % 100;
    printA(); // Should still print the old value of a

    // 3. Capturing variables by reference
    int z = 2;
    auto addToZ = [&z](int y) { z += y; };
    addToZ(3);
    std::cout << "Value of z after adding 3 is: " << z << std::endl;

    int cc = 10;

    auto f1 = [cc]() { std::cout << "value capture: " << cc << std::endl; };
    auto f2 = [&cc]() { std::cout << "ref capture:   " << cc << std::endl; };

    cc = 20;

    f1();  // 10
    f2();  // 20

    // mutable test
    int dd = 5;
    auto m1 = [dd] () {
        // ++dd;        // syntax error
        std::cout << dd << std::endl;
    };
    m1();

    auto m2 = [dd] mutable {
        dd++;
        std::cout << dd << std::endl;
    };

    m2();
    m2();

    std::cout << dd << std::endl;

    return ret;
}