#pragma once

#include <stdexcept>
#include <string>

class ConfigParseError : public std::exception {
public:
    explicit ConfigParseError(const std::string& message) : message_(message) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
private:
    std::string message_;
};