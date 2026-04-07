#include <gtest/gtest.h>
#include "ConfigParser.h"
#include "exceptions.h"
#include <filesystem>
#include <fstream>
#include <string>

class ConfigParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        tempFilename = std::filesystem::temp_directory_path() / "temp_config.json";
        if (std::filesystem::exists(tempFilename)) {
            std::filesystem::remove(tempFilename);
        }
    }

    void TearDown() override {
        if (std::filesystem::exists(tempFilename)) {
            std::filesystem::remove(tempFilename);
        }
    }

    std::string createTempFile(const std::string& content) {
        std::ofstream file(tempFilename);
        file << content;
        file.close();
        return tempFilename.string();
    }

    std::filesystem::path tempFilename;
};

TEST_F(ConfigParserTest, ValidConfig) {
    std::string json = R"(
{
    "port": 8080,
    "host": "localhost",
    "enable_logging": true
}
)";
    std::string filename = createTempFile(json);
    Config config = ConfigParser::parseConfig(filename);
    EXPECT_EQ(config.port, 8080);
    EXPECT_EQ(config.host, "localhost");
    EXPECT_TRUE(config.enable_logging);
}

TEST_F(ConfigParserTest, MissingPort) {
    std::string json = R"(
{
    "host": "localhost",
    "enable_logging": true
}
)";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, InvalidPortType) {
    std::string json = R"(
{
    "port": "8080",
    "host": "localhost",
    "enable_logging": true
}
)";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, MissingHost) {
    std::string json = R"(
{
    "port": 8080,
    "enable_logging": true
}
)";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, InvalidHostType) {
    std::string json = R"(
{
    "port": 8080,
    "host": 123,
    "enable_logging": true
}
)";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, MissingEnableLogging) {
    std::string json = R"(
{
    "port": 8080,
    "host": "localhost"
}
)";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, InvalidEnableLoggingType) {
    std::string json = R"(
{
    "port": 8080,
    "host": "localhost",
    "enable_logging": "true"
}
)";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, InvalidJson) {
    std::string json = "{ invalid json }";
    std::string filename = createTempFile(json);
    EXPECT_THROW(ConfigParser::parseConfig(filename), ConfigParseError);
}

TEST_F(ConfigParserTest, FileNotFound) {
    EXPECT_THROW(ConfigParser::parseConfig("nonexistent.json"), ConfigParseError);
}