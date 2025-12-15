#ifndef LEARNCPP_FILE_H
#define LEARNCPP_FILE_H

#include <cstdio>
#include <string>


class File {
private:
    FILE* fp;

public:
    explicit File(const std::string& filename, const char *mode = "a");

    ~File() noexcept;

    // 禁用拷贝构造函数和拷贝赋值运算符
    File(File& file) = delete;
    File& operator=(File& file) = delete;

    // 启用移动构造函数和移动赋值运算符
    File(File&& other) noexcept;
    File& operator=(File&& other) noexcept;

    void write(const std::string& message);
    void flush();
};


#endif //LEARNCPP_FILE_H