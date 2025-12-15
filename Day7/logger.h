#ifndef LEARNCPP_LOGGER_H
#define LEARNCPP_LOGGER_H

#include "File.h"


class logger {
    File file;
    std::string current_time() const;
public:

    explicit logger(const std::string &filename);
    void debug(const std::string &message);
    void info(const std::string &message);
    void warn(const std::string &message);
    void error(const std::string &message);

    logger(logger& lg) = delete;
    logger& operator=(logger& lg) = delete;

    logger(logger&& other) noexcept = default;
    logger& operator=(logger&& other) noexcept = default;

    // 不写析构，让C++自己实现
    // ~logger();
};


#endif //LEARNCPP_LOGGER_H