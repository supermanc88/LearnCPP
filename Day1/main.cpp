#include <iostream>

using ulong = unsigned long;
using uint = unsigned int;
using ushort = unsigned short;
using uchar = unsigned char;

namespace my {
    void func() {
        std::cout << "This is my namespace function." << std::endl;
    }
}

int main() {
    std::string s = "Hello, World!";

    ulong long_var = 100;
    uint int_var = 200;
    ushort short_var = 300;
    uchar char_var = 'C';

    std::cout << "long_var: " << long_var << ", sizeof: " << sizeof(long_var) << std::endl;
    std::cout << "int_var: " << int_var << ", sizeof: " << sizeof(int_var) << std::endl;
    std::cout << "short_var: " << short_var << ", sizeof: " << sizeof(short_var) << std::endl;
    std::cout << "char_var: " << char_var << ", sizeof: " << sizeof(char_var) << std::endl;

    auto x = 10;
    auto y = 20.5;
    auto z = 'A';
    auto ss = "specific string";

    decltype(x) a = 15;        // a is of type int
    decltype(y) b = 25.5;     // b is of type double
    decltype(z) c = 'B';      // c is of type char
    decltype(ss) t = "another string"; // t is of type const char*

    s += " from C++";
    std::cout << "hello C++" << std::endl;
    std::cout << s << std::endl;

    std::cout << "x: " << x << ", y: " << y << ", z: " << z << "ss: " << ss << std::endl;
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << ", t: " << t << std::endl;

    my::func();

    return 0;
}