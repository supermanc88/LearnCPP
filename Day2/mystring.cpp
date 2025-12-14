#include <iostream>

class MyString {
private:
    char *data;
    size_t length;

public:
    MyString(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        std::cout << "Copy constructor called" << std::endl;
    }
    ~MyString() {
        delete[] data;
        std::cout << "Destructor called for string: " << std::endl;
    }
    void print() const {
        std::cout << data << std::endl;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;

    const char *text = "Sample MyString";
    MyString myStr1(text);
    myStr1.print();

    MyString myStr2 = myStr1; // Invokes copy constructor
    myStr2.print();

    return 0;
}