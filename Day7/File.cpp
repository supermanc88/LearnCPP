#include <iostream>
#include "File.h"

File::File(const std::string &filename, const char *mode) {
    fp = fopen(filename.c_str(), mode);
    if (fp == nullptr) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

File::~File() noexcept {
    if (fp != nullptr) {
        std::cout << "Closing file." << std::endl;
        fclose(fp);
    }
}

File::File(File &&other) noexcept
            :fp(other.fp) {
    other.fp = nullptr;
}

File & File::operator=(File &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    if (fp != nullptr) {
        fclose(fp);
    }
    fp = other.fp;
    other.fp = nullptr;
    return *this;
}

void File::write(const std::string &message) {
    fwrite(message.c_str(), 1, message.size(), fp);
}

void File::flush() {
    fflush(fp);
}
