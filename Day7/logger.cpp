#include "logger.h"

std::string logger::current_time() const {
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t now_time_t = system_clock::to_time_t(now);
    auto tm = *std::localtime(&now_time_t);

    char buf[64];
    std::strftime(buf, sizeof(buf), "%F %T", &tm);
    return buf;
}

logger::logger(const std::string &filename)
            :file(filename, "a") {
}

void logger::debug(const std::string &message) {
    file.write("[" + current_time() + "] [DEBUG] " + message + "\n");
    file.flush();
}

void logger::info(const std::string &message) {
    file.write("[" + current_time() + "] [INFO] " + message + "\n");
    file.flush();
}

void logger::warn(const std::string &message) {
    file.write("[" + current_time() + "] [WARN] " + message + "\n");
}

void logger::error(const std::string &message) {
    file.write("[" + current_time() + "] [ERROR] " + message + "\n");
}
