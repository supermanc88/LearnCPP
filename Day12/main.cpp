#include <iostream>

template <typename T>
T add(T a, T b) {
    return a + b;
}


template <typename T>
class Container {
public:
    void setValue(T val) {
        value = val;
    }
    T getValue() const {
        return value;
    }
private:
    T value;
};



int main() {
    int ret = 0;
    std::cout << "Template Test" << std::endl;

    // Test the add function
    int sumInt = add<int>(3, 5);
    std::cout << "Sum of integers: " << sumInt << std::endl;

    double sumDouble = add<double>(2.5, 4.5);
    std::cout << "Sum of doubles: " << sumDouble << std::endl;

    Container<int> intContainer;
    intContainer.setValue(42);
    std::cout << "Container Value: " << intContainer.getValue() << std::endl;




    return ret;
}