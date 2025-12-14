#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    std::string item;
    for (char ch : s) {
        if (ch != delim) {
            item += ch;
        } else {
            if (!item.empty()) {
                elems.push_back(item);
                item.clear();
            }
        }
    }
    if (!item.empty()) {
        elems.push_back(item);
    }
    return elems;
}

int main() {
    auto r = split("a,b,c,d", ',');
    // 打印结果
    for (std::string& str : r) {
        std::cout << str << std::endl;
    }
    std::cout << "----" << std::endl;
    for (std::string str : r) {
        std::cout << str << std::endl;
    }
}
