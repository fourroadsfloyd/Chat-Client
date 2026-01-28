#ifndef ASYNCLOG_H
#define ASYNCLOG_H

//#define FMT_HEADER_ONLY

#include <string>
#include <thread>
#include <fstream>
#include <atomic>
#include <sstream>
#include <vector>
#include <chrono>
//#include <fmt/format.h>
#include "tool/CircleQueue.h"

static const size_t MAX_CAPACITY = 200;

enum class LogLevel { LogINFO, LogWARNING, LogERROR };

template<typename T>
std::string to_string_helper(T&& arg)
{
    std::ostringstream oss;
    oss << std::forward<T>(arg);
    return oss.str();
}

class AsyncLog {
public:
    static AsyncLog& getInstance(const std::string& filename = "..\\..\\..\\..\\Client_.log")
    {
        static AsyncLog instance(filename);
        return instance;
    }

    template<typename... Args>
    void log(LogLevel level, const std::string& format, Args&&... args) {
        std::string level_str;
        switch(level) {
        case LogLevel::LogINFO: level_str = "[INFO] "; break;
        case LogLevel::LogWARNING: level_str = "[WARNING] "; break;
        case LogLevel::LogERROR: level_str = "[ERROR] "; break;
        }
        log_queue_.push("[" + getCurrentTime() + "] " + level_str + formatMessage(format, std::forward<Args>(args)...));
    }

private:
    AsyncLog(const std::string& filename) : log_file_(filename, std::ios::out | std::ios::app), exit_flag_(false)
    {
        if (!log_file_.is_open()) 
        {
            throw std::runtime_error("无法打开日志文件");   
        }

        log_queue_.setCapacity(MAX_CAPACITY);

        worker_thread_ = std::thread(&AsyncLog::processQueue, this);
    }

    ~AsyncLog()
    {
        log_queue_.shutdown();
        if (worker_thread_.joinable())
        {
            worker_thread_.join();
        }
        if (log_file_.is_open()) {
            log_file_.close();
        }
    }

    void processQueue()
    {
        std::string msg;
        while (log_queue_.pop(msg)) 
        {
            log_file_ << msg << std::endl;
        }
    }

    std::string getCurrentTime() 
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        char buffer[100];
        std::tm timeinfo;
        localtime_s(&timeinfo, &now_time);
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        return std::string(buffer);
    }

    template<typename... Args>
    std::string formatMessage(const std::string& format, Args&&... args) 
    {
        /*try 
        {
            return fmt::format(format, std::forward<Args>(args)...);
        }
        catch (const fmt::format_error& e) 
        {   */        
            std::vector<std::string> arg_strings = { to_string_helper(std::forward<Args>(args))... };
            std::ostringstream oss;
            size_t arg_index = 0;
            size_t pos = 0;
            size_t placeholder = format.find("{}", pos);

            while (placeholder != std::string::npos) 
            {
                oss << format.substr(pos, placeholder - pos);

                if (arg_index < arg_strings.size()) 
                {
                    oss << arg_strings[arg_index++];
                }
                else 
                {
                    oss << "{}";
                }

                pos = placeholder + 2;
                placeholder = format.find("{}", pos);
            }

            oss << format.substr(pos);

            while (arg_index < arg_strings.size()) 
            {
                oss << arg_strings[arg_index++];
            }

            return oss.str();
        //}
    }

private:
    CircleQueue<std::string> log_queue_;
    std::thread worker_thread_;
    std::ofstream log_file_;
    std::atomic<bool> exit_flag_;

};


#endif  
