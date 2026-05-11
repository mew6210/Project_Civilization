#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <filesystem>

enum class LogLevel {
    SUCCESS,
    WARNING,
    ERROR,
    INFO
};

class Logger {
public:
    Logger(const std::string& filename = "logs/log.txt");
    ~Logger();

    //Errorlog
    template<typename... Args>
    void errorLog(bool crash, Args&&... args) {
        logInternal(LogLevel::ERROR, std::forward<Args>(args)...);
        if (crash) {
            std::exit(EXIT_FAILURE);
        }
    }

    //Other logs
    template<typename... Args>
    void successLog(Args&&... args) {
        logInternal(LogLevel::SUCCESS, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warningLog(Args&&... args) {
        logInternal(LogLevel::WARNING, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void infoLog(Args&&... args) {
        logInternal(LogLevel::INFO, std::forward<Args>(args)...);
    }

private:
    std::ofstream fileStream;
    bool useColors = false;

    //Function that colors and puts text together
    template<typename... Args>
    void logInternal(LogLevel level, Args&&... args) {
        std::string symbol;
        std::string colorCode;

        switch (level) {
        case LogLevel::SUCCESS: symbol = "+"; colorCode = "\033[32m"; break;
        case LogLevel::WARNING: symbol = "?"; colorCode = "\033[33m"; break;
        case LogLevel::ERROR:   symbol = "-"; colorCode = "\033[31m"; break;
        case LogLevel::INFO:    symbol = "i"; colorCode = "\033[36m"; break;
        }

        std::cout << "[";
        if (useColors) std::cout << colorCode;
        std::cout << symbol;
        if (useColors) std::cout << "\033[0m";
        std::cout << "] ";

        (std::cout << ... << std::forward<Args>(args));
        std::cout << std::endl;

        if (fileStream.is_open()) {
            fileStream << "[ " << symbol << " ] ";
            (fileStream << ... << std::forward<Args>(args));
            fileStream << std::endl;
        }
    }

    bool setupConsole();
};

extern Logger defaultLogger;