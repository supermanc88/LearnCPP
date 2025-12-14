#include <iostream>

class Person {
public:
    std::string name;
    int age;

    Person(const std::string& name, int age) :
        name(name), age(age) {
        std::cout << "copy ctor called" << std::endl;
    }

    ~Person() {
        std::cout << "dtor called for " << name << std::endl;
    }

    void hello() const{
        std::cout << "Hello, my name is " << name << " and I am " << age << " years old." << std::endl;
    }
};


int main() {

    Person alice("Alice", 30);
    alice.hello();

    return 0;
}