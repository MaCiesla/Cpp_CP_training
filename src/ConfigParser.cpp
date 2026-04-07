#include "ConfigParser.h"
#include "exceptions.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

Config ConfigParser::parseConfig(const std::string& filepath) {
    std::cout << "Starting to parse config from file: " << filepath << std::endl;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Failed to open config file: " << filepath << std::endl;
        throw ConfigParseError("Failed to open config file: " + filepath);
    }

    nlohmann::json j;
    try {
        file >> j;
    } catch (const nlohmann::json::parse_error& e) {
        std::cout << "JSON parse error: " << e.what() << std::endl;
        throw ConfigParseError("JSON parse error: " + std::string(e.what()));
    }

    std::cout << "JSON loaded successfully" << std::endl;

    // Validate and parse fields
    Config config;

    if (!j.contains("port") || !j["port"].is_number_integer()) {
        std::cout << "Missing or invalid 'port' field" << std::endl;
        throw ConfigParseError("Missing or invalid 'port' field");
    }
    config.port = j["port"];

    if (!j.contains("host") || !j["host"].is_string()) {
        std::cout << "Missing or invalid 'host' field" << std::endl;
        throw ConfigParseError("Missing or invalid 'host' field");
    }
    config.host = j["host"];

    if (!j.contains("enable_logging") || !j["enable_logging"].is_boolean()) {
        std::cout << "Missing or invalid 'enable_logging' field" << std::endl;
        throw ConfigParseError("Missing or invalid 'enable_logging' field");
    }
    config.enable_logging = j["enable_logging"];

    std::cout << "Config parsed and validated successfully" << std::endl;

    return config;
}