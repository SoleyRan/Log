#include <chrono>
#include <thread>
#include <log.hpp>

int main()
{
    std::string log_path = "/home/work/log/";
    int console_log_level = 2;
    int file_log_level = 3;
    int max_log_size = 10;
    int max_log_num = 10;
    goodlog::logInit(log_path, console_log_level, file_log_level, max_log_size, max_log_num);

    for(int i = 0; i < 1000; ++i)
    {
        LOG_Debug() << "This is debug msg...";
        LOG_Info() << "This is info msg...";
        LOG_Warn() << "This is warning msg...";
        LOG_Error() << "This is error msg...";
        LOG_Fatal() << "This is fatal msg...";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}