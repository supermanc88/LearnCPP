#include <iostream>

#include "logger.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    logger lg("app.log");
    lg.info("Application started");
    lg.debug("This is a debug message");

    logger lg2 = std::move(lg);
    lg2.warn("This is a warning message after move");
    lg2.error("This is an error message after move");

    return 0;
}