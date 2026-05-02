# GoodLog

A lightweight C++17 logging wrapper around Boost.Log with colored console output, automatic source location, rotating log files, severity filtering, and binary hex dump helpers.

GoodLog is designed for C++ services, robotics tools, middleware modules, and debugging-heavy applications that need practical logging without rewriting the same Boost.Log setup in every project.

## Why GoodLog?

Boost.Log is powerful, but the setup can become verbose when a project only needs a clean daily workflow: initialize logging once, print readable messages, keep rotated files, and filter noisy output by severity or channel.

GoodLog keeps Boost.Log as the backend and provides a smaller macro-based interface for everyday development.

## Features

- C++17 logging wrapper built on Boost.Log
- `trace`, `debug`, `info`, `warning`, `error`, and `fatal` severity levels
- Automatic `file:line` source location in each log call
- Colored console prefixes for important severities
- Rotating file sink with max file size and max file count control
- Console and file severity thresholds can be configured separately
- Optional channel filtering during initialization
- Hex dump helpers for binary buffers and protocol debugging
- CMake build with demo and GoogleTest targets

## Quick Start

```bash
git clone https://github.com/SoleyRan/Log.git
cd Log
cmake -S . -B build
cmake --build build
./build/demo/log_demo
```

By default, the demo writes rotated log files under `/tmp/goodlog/`.

## Basic Usage

```cpp
#include <log.hpp>

int main()
{
    const std::string log_path = "/tmp/goodlog/";
    const int console_log_level = 2; // info and above
    const int file_log_level = 1;    // debug and above
    const int max_log_size_mb = 10;
    const int max_log_files = 10;

    goodlog::logInit(
        log_path,
        console_log_level,
        file_log_level,
        max_log_size_mb,
        max_log_files
    );

    LOG_Debug() << "debug details";
    LOG_Info()  << "service started";
    LOG_Warn()  << "using fallback config";
    LOG_Error() << "connection failed";
    LOG_Fatal() << "unrecoverable error";

    return 0;
}
```

## Output Shape

GoodLog formats records with timestamp, severity, source location, and your message:

```text
[2026-05-02 10:24:18.123456]<info>[main.cpp:18]:service started
[2026-05-02 10:24:18.123789]<warning>[main.cpp:19]:using fallback config
[2026-05-02 10:24:18.124000]<error>[main.cpp:20]:connection failed
```

Log files are written with a sortable counter and timestamp pattern:

```text
00000-2026-05-02-10-24-18.log
00001-2026-05-02-10-27-42.log
```

## Severity Levels

The `console_log_level` and `file_log_level` arguments map to Boost.Log trivial severities:

| Value | Severity |
| --- | --- |
| `0` | trace |
| `1` | debug |
| `2` | info |
| `3` | warning |
| `4` | error |
| `5` | fatal |

This makes it easy to keep terminal output quiet while preserving more detail in log files.

## Hex Dump Helpers

GoodLog includes helpers for binary data inspection, useful when debugging packets, sensors, middleware frames, or custom protocols.

```cpp
std::array<unsigned char, 4> payload = {0x12, 0x34, 0xab, 0xcd};

LOG_DEBUG_HEX(payload.data(), payload.size(), "rx payload");
```

## Build Options

The root CMake project exposes demo and test switches:

```bash
cmake -S . -B build -DBUILD_DEMO=ON -DBUILD_TEST=ON
cmake --build build
ctest --test-dir build
```

Dependencies:

- C++17 compiler
- CMake 3.5+
- Boost with Log, Filesystem, Thread, System, and Log Setup libraries
- GoogleTest when `BUILD_TEST=ON`

## Project Layout

```text
.
|-- CMakeLists.txt
|-- demo/
|   `-- log_demo.cpp
|-- src/
|   |-- log.hpp
|   |-- text_file_backend_self_defined.cpp
|   `-- text_file_backend_self_defined.hpp
`-- test/
    `-- log_test.cpp
```

## When To Use It

GoodLog is a good fit when you want a small C++ logging layer for an application, tool, or middleware module and you already use Boost in your stack.

For a large public framework, a cross-platform package manager release, or a dependency-free logger, this project may need more hardening first.

## Roadmap

- Add install/export targets for easier downstream CMake integration
- Add CI builds for Ubuntu
- Add a screenshot of colored terminal output
- Add package examples for application integration
- Clean up channel macro namespace consistency
- Add a public license before wider reuse
