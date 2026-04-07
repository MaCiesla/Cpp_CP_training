# JSON Config Parser

A small C++ project that loads and validates JSON configuration files.

## Features

- Parse JSON configuration from a file
- Validate required fields:
  - `port` (int)
  - `host` (string)
  - `enable_logging` (bool)
- Throw exceptions on invalid JSON or missing/incorrect fields
- Unit tests using GoogleTest
- CMake build setup
- GitHub Actions workflow for CI

## Build Instructions

From the repository root:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

If `cmake` is not on your `PATH`, use the full installation path or add it to your environment.

## Run Tests

```powershell
ctest --test-dir build --output-on-failure -C Debug
```

If `ctest` is not on your `PATH`, use the full installation path or add it to your environment.

Or run the test executable directly:

```powershell
.\build\Debug\config_parser_tests.exe
```

## Run the Example Application

From the repository root:

```powershell
.\build\Debug\json_config_app.exe
```

The application reads `examples/config.json` and prints the parsed values.

## JSON Config Format

Example `config.json`:

```json
{
  "port": 8080,
  "host": "localhost",
  "enable_logging": true
}
```

## Project Structure

- `CMakeLists.txt` - top-level CMake project and dependency setup
- `README.md` - project overview, build/test instructions, and usage examples
- `.gitignore` - files and folders to ignore in source control
- `.github/workflows/ci.yml` - GitHub Actions pipeline for building and testing on Linux, Windows, and macOS

- `include/ConfigParser.h` - public parser API and `Config` data structure
- `include/exceptions.h` - custom exception type for config errors
- `src/ConfigParser.cpp` - JSON loading, parsing, and field validation implementation
- `src/main.cpp` - example application entrypoint that reads `examples/config.json` and prints parsed values

- `tests/ConfigParserTest.cpp` - GoogleTest cases covering valid config parsing, missing fields, invalid types, invalid JSON, and missing files
- `examples/config.json` - sample configuration file used by the example application

## Notes

- Uses `nlohmann/json` for JSON parsing
- Uses `GoogleTest` for unit tests
- Logging is currently implemented with console output
