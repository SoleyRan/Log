# GoodLog
<img width="1280" height="640" alt="goodlog-readme-banner-1280x640" src="https://github.com/user-attachments/assets/9387939a-d1c9-4a76-bd01-3c8ae888889d" />

[English](README.md) | 简体中文

GoodLog 是一个基于 Boost.Log 封装的轻量级 C++17 日志库，支持彩色终端输出、自动源码位置、日志文件轮转、日志级别过滤和二进制 Hex Dump 辅助能力。

GoodLog 面向 C++ 服务程序、机器人/自动驾驶中间件、调试密集型模块，以及已经在项目中使用 Boost 的工程。它的目标不是替代完整日志框架，而是把常见 Boost.Log 配置封装成更容易复用的接口。

## 预览

![GoodLog terminal output](docs/goodlog-terminal.jpg)

## 为什么做 GoodLog？

Boost.Log 功能很强，但在普通工程里，每次配置 console sink、file sink、formatter、日志轮转、collector、severity filter 都比较繁琐。

GoodLog 保留 Boost.Log 作为后端，同时提供更小、更直接的宏接口，让日常日志调用更简单。

## 功能特性

- 基于 Boost.Log 的 C++17 日志封装
- 支持 `trace`、`debug`、`info`、`warning`、`error`、`fatal` 六个日志级别
- 每条日志自动带上 `file:line` 源码位置
- 重要级别支持彩色终端前缀
- 文件 sink 支持按文件大小和文件数量轮转
- 支持可选 gzip 压缩和 AES-256-GCM 加密日志文件
- 终端输出和文件输出可以分别设置日志级别阈值
- 初始化时可选 channel 过滤
- 支持二进制 buffer 的 Hex Dump
- 支持 CMake 构建 demo 和 GoogleTest 测试
- 支持安装为 CMake package，并通过 `find_package(GoodLog)` 使用

## 环境要求

GoodLog 当前主要面向 Linux 和 WSL。当前 CMake 文件会链接 `pthread`、`dl`、`rt` 等 Linux 系统库，因此原生 Windows 和 macOS 构建可能还需要少量 CMake 适配。

构建库和 demo 需要：

- C++17 编译器，例如 `g++` 或 `clang++`
- CMake 3.5+
- Boost 开发库，包括 `Boost.Log`、`Boost.LogSetup`、`Boost.Filesystem`、`Boost.Thread` 和 `Boost.System`
- zlib 开发库，用于 gzip 压缩
- OpenSSL 开发库，用于 AES-256-GCM 加密

构建测试额外需要：

- GoogleTest 开发包

如果只想构建并运行 demo，可以使用 `-DBUILD_TEST=OFF` 关闭测试。

## 安装依赖

### Ubuntu / Debian / WSL

```bash
sudo apt update
sudo apt install -y build-essential cmake libboost-all-dev libssl-dev zlib1g-dev libgtest-dev
```

启用测试构建：

```bash
git clone https://github.com/SoleyRan/Log.git
cd Log
cmake -S . -B build -DBUILD_DEMO=ON -DBUILD_TEST=ON
cmake --build build
ctest --test-dir build
./build/demo/log_demo
```

如果不想安装 GoogleTest，只构建库和 demo：

```bash
git clone https://github.com/SoleyRan/Log.git
cd Log
cmake -S . -B build -DBUILD_DEMO=ON -DBUILD_TEST=OFF
cmake --build build
./build/demo/log_demo
```

### Fedora

```bash
sudo dnf install -y gcc-c++ cmake boost-devel openssl-devel zlib-devel gtest-devel
```

然后使用上面的 CMake 构建命令即可。

### macOS

macOS 目前不是主要测试目标。可以先通过 Homebrew 安装基础依赖：

```bash
brew install cmake boost openssl zlib googletest
```

当前 CMake 文件里仍有 Linux 相关链接配置，因此 macOS 可能需要进一步清理 CMake 后才能顺利构建。

### Windows

Windows 用户当前推荐使用 WSL Ubuntu：

```powershell
wsl --install
```

进入 Ubuntu 后，按照 Ubuntu / Debian / WSL 的依赖安装方式继续即可。

原生 Windows 支持还没有完整文档，因为当前 CMake 文件使用了 Linux 相关系统库。

## 快速开始

在 Linux/WSL 下，不构建测试的最小流程：

```bash
git clone https://github.com/SoleyRan/Log.git
cd Log
cmake -S . -B build -DBUILD_TEST=OFF
cmake --build build
./build/demo/log_demo
```

默认情况下，demo 会把轮转日志写到 `/tmp/goodlog/`。

## 安装为 CMake Package

GoodLog 可以安装到指定 prefix，然后在其他 CMake 项目里通过 `find_package(GoodLog)` 使用。

安装到用户本地目录：

```bash
git clone https://github.com/SoleyRan/Log.git
cd Log
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_DEMO=OFF -DBUILD_TEST=OFF
cmake --build build
cmake --install build --prefix "$HOME/.local"
```

安装到系统目录：

```bash
git clone https://github.com/SoleyRan/Log.git
cd Log
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_DEMO=OFF -DBUILD_TEST=OFF
cmake --build build
sudo cmake --install build --prefix /usr/local
```

安装后的目录结构大致如下：

```text
<prefix>/
|-- include/goodlog/
|   |-- log.hpp
|   `-- text_file_backend_self_defined.hpp
|-- lib/
|   `-- libgood_log.so
`-- lib/cmake/GoodLog/
    |-- GoodLogConfig.cmake
    |-- GoodLogConfigVersion.cmake
    |-- GoodLogTargets.cmake
    `-- GoodLogTargets-*.cmake
```

在其他 CMake 项目中使用：

```cmake
cmake_minimum_required(VERSION 3.5)
project(MyApp LANGUAGES CXX)

find_package(GoodLog REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE GoodLog::good_log)
```

然后在源码中包含 GoodLog：

```cpp
#include <log.hpp>

int main()
{
    goodlog::logInit("/tmp/my_app_logs/", 2, 1, 10, 10);
    LOG_Info() << "hello from installed GoodLog";
    return 0;
}
```

如果 GoodLog 安装在自定义 prefix，需要配置应用时通过 `CMAKE_PREFIX_PATH` 指定：

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="$HOME/.local"
cmake --build build
```

## 创建发布包

可以先安装到临时目录，再打包成 GitHub Release 附件：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_DEMO=OFF -DBUILD_TEST=OFF
cmake --build build
cmake --install build --prefix package/goodlog-0.1.0
tar -C package -czf goodlog-0.1.0-linux-x86_64.tar.gz goodlog-0.1.0
```

用户解压后，通过 `CMAKE_PREFIX_PATH` 指向解压目录即可。

## 基本用法

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

## 压缩和加密

`logInit` 保留原有位置参数，同时新增可选的 `goodlog::LogOptions` 参数，用于控制日志落盘前的压缩和加密：

```cpp
goodlog::LogOptions options;
options.compression = goodlog::CompressionMode::Gzip;
options.encryption = goodlog::EncryptionMode::Aes256Gcm;
options.encryption_key_hex = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";

goodlog::logInit(
    "/tmp/goodlog/",
    2,
    1,
    10,
    10,
    options
);
```

旧调用方式仍然兼容：

```cpp
goodlog::logInit("/tmp/goodlog/", 2, 1, 10, 10);
```

落盘模式：

| 压缩 | 加密 | 输出 |
| --- | --- | --- |
| `CompressionMode::None` | `EncryptionMode::None` | 普通 `.log` 文本 |
| `CompressionMode::Gzip` | `EncryptionMode::None` | 标准 gzip 流，`.log.gz` |
| `CompressionMode::None` | `EncryptionMode::Aes256Gcm` | AES-256-GCM 逐条记录 envelope，`.log.enc` |
| `CompressionMode::Gzip` | `EncryptionMode::Aes256Gcm` | 逐条 gzip 后再 AES-256-GCM 加密，`.log.gz.enc` |

加密密钥需要使用 32 字节 key，并编码成 64 位 hex 字符串。生产环境不要把密钥硬编码进源码，建议从部署系统的 secret 或配置层读取。

## 输出格式

GoodLog 默认输出时间戳、级别、源码位置和消息：

```text
[2026-05-02 10:24:18.123456]<info>[main.cpp:18]:service started
[2026-05-02 10:24:18.123789]<warning>[main.cpp:19]:using fallback config
[2026-05-02 10:24:18.124000]<error>[main.cpp:20]:connection failed
```

日志文件会使用可排序的序号和时间戳命名：

```text
00000-2026-05-02-10-24-18.log
00001-2026-05-02-10-27-42.log
```

## 日志级别

`console_log_level` 和 `file_log_level` 分别控制终端输出和文件输出的最低级别：

| 数值 | 级别 |
| --- | --- |
| `0` | trace |
| `1` | debug |
| `2` | info |
| `3` | warning |
| `4` | error |
| `5` | fatal |

这样可以让终端输出保持清爽，同时在文件里保留更多调试信息。

## Hex Dump 辅助宏

GoodLog 提供二进制数据检查辅助能力，适合调试网络包、传感器数据、中间件消息或自定义协议。

```cpp
std::array<unsigned char, 4> payload = {0x12, 0x34, 0xab, 0xcd};

LOG_DEBUG_HEX(payload.data(), payload.size(), "rx payload");
```

## 构建选项

顶层 CMake 项目提供 demo 和测试开关：

```bash
cmake -S . -B build -DBUILD_DEMO=ON -DBUILD_TEST=ON
cmake --build build
ctest --test-dir build
```

| 选项 | 默认值 | 说明 |
| --- | --- | --- |
| `BUILD_DEMO` | `ON` | 构建 `demo/log_demo.cpp` |
| `BUILD_TEST` | `ON` | 构建 `test/` 下的 GoogleTest 测试 |

常用构建方式：

```bash
# 只构建库和 demo
cmake -S . -B build -DBUILD_DEMO=ON -DBUILD_TEST=OFF

# 只构建库
cmake -S . -B build -DBUILD_DEMO=OFF -DBUILD_TEST=OFF

# 构建 demo 和测试
cmake -S . -B build -DBUILD_DEMO=ON -DBUILD_TEST=ON
```

## 常见问题

如果 CMake 找不到 Boost，请确认已经安装 Boost 开发包：

```bash
sudo apt install -y libboost-all-dev
```

如果 CMake 找不到 GTest，可以安装它，或者关闭测试：

```bash
sudo apt install -y libgtest-dev
cmake -S . -B build -DBUILD_TEST=ON
```

或者：

```bash
cmake -S . -B build -DBUILD_TEST=OFF
```

如果你的应用找不到已安装的 GoodLog package，请通过 `CMAKE_PREFIX_PATH` 指定安装路径：

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="$HOME/.local"
```

如果 demo 能运行但看不到日志文件，请检查默认输出目录：

```bash
ls -la /tmp/goodlog/
```

## 项目结构

```text
.
|-- CMakeLists.txt
|-- cmake/
|   `-- GoodLogConfig.cmake.in
|-- demo/
|   `-- log_demo.cpp
|-- src/
|   |-- log.hpp
|   |-- text_file_backend_self_defined.cpp
|   `-- text_file_backend_self_defined.hpp
`-- test/
    `-- log_test.cpp
```

## 适用场景

GoodLog 适合用于已经依赖 Boost 的 C++ 应用、工具或中间件模块，并且希望快速获得一个小型日志封装层。

如果你需要完全无依赖日志库、跨平台包管理器发布，或者企业级完整日志框架，GoodLog 还需要继续打磨。

## 路线图

- 添加 Ubuntu CI 构建
- 增加 package 集成示例
- 清理 channel 宏的命名空间一致性
- 改进原生 Windows 和 macOS CMake 支持

## License

GoodLog 使用 MIT License。英文原文见 [LICENSE](LICENSE)，非官方中文译文见 [LICENSE.zh-CN.md](LICENSE.zh-CN.md)。
