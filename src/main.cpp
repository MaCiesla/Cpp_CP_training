#include "ConfigParser.h"
#include "exceptions.h"
#include <filesystem>
#include <iostream>

static std::filesystem::path findConfigPath() {
    const std::filesystem::path relativePath = "examples/config.json";
    std::filesystem::path current = std::filesystem::current_path();

    for (int depth = 0; depth < 4; ++depth) {
        std::filesystem::path candidate = current / relativePath;
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
        current = current.parent_path();
        if (current.empty()) {
            break;
        }
    }

    return relativePath;
}

int main() {
    const std::filesystem::path configPath = findConfigPath();

    try {
        Config config = ConfigParser::parseConfig(configPath.string());
        std::cout << "Config values:\n";
        std::cout << "  port: " << config.port << "\n";
        std::cout << "  host: " << config.host << "\n";
        std::cout << std::boolalpha;
        std::cout << "  enable_logging: " << config.enable_logging << "\n";
        return 0;
    } catch (const ConfigParseError& error) {
        std::cerr << "Failed to load config: " << error.what() << "\n";
        return 1;
    }
}
