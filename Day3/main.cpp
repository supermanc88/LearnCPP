#include <iostream>

class File {
private:
    FILE*  filePtr;
public:
    File(const char* filename, const char* mode) {
        filePtr = fopen(filename, mode);
        if (!filePtr) {
            std::cerr << "Error opening file: " << filename << std::endl;
        }
    }

    ~File() {
        if (filePtr) {
            std::cout << "Closing file." << std::endl;
            fclose(filePtr);
        }
    }

    size_t write(const char* data, size_t size) {
        if (!filePtr) return 0;
        return fwrite(data, 1, size, filePtr);
    }
};

int main() {
    File myFile("example.txt", "w");
    const char* text = "Hello, World!\n";
    myFile.write(text, strlen(text));
    return 0;
}