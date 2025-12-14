#include <iostream>

class MyString {
private:
    char *data;
    size_t length;
public:
    MyString(const char *str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        std::cout << "Constructor called for: " << data << std::endl;
    }
    // MyString(const char *str) = delete; // Disable constructor from const char*
    MyString(const MyString &other) = delete; // Disable copy constructor

    MyString(MyString &&other) noexcept : data(other.data), length(other.length) {
        std::cout << "Move constructor called" << std::endl;
        other.data = nullptr;
        other.length = 0;
    }

    MyString& operator=(const MyString &other) {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    MyString& operator=(MyString &&other) noexcept {
        std::cout << "Move assignment operator called" << std::endl;
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }
};


int main() {

    std::string a = "123";
    std::string b = a;      // Copy constructor
    std::string c = std::move(a);  // Move constructor
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;


    MyString str1("Hello");
    MyString str2 = std::move(str1); // Move constructor
    MyString str3(std::move(str2)); // Move constructor

    std::cout << "str1, str2, str3 created and moved." << std::endl;


    return 0;
}