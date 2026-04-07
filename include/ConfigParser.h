#pragma once

#include <string>

struct Config {
    int port;
    std::string host;
    bool enable_logging;
};

class ConfigParser {
public:
    static Config parseConfig(const std::string& filepath);
};