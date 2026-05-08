#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

enum class LogLevel {
    SUCCESS,
    WARNING,
    ERROR,
    INFO
};

class Logger {
public:
    Logger(const std::string& filename = "log.txt");
    ~Logger();

    //Errorlog
    template<typename... Args>
    void errorLog(bool crash, Args&&... args) {
        logInternal(LogLevel::ERROR, std::forward<Args>(args)...);
        if (crash) {
            std::cerr << "\033[31m!!! FATAL ERROR: Program terminated !!!\033[0m" << std::endl;
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

    //Function that colors and puts text together
    template<typename... Args>
    void logInternal(LogLevel level, Args&&... args) {
        std::string prefix;
        std::string colorCode;

        switch (level) {
        case LogLevel::SUCCESS: prefix = "[+] "; colorCode = "\033[32m"; break; //Green
        case LogLevel::WARNING: prefix = "[?] "; colorCode = "\033[33m"; break; //Yellow
        case LogLevel::ERROR:   prefix = "[-] "; colorCode = "\033[31m"; break; //Red
        case LogLevel::INFO:    prefix = "[i] "; colorCode = "\033[36m"; break; //Turquoise
        }

        std::cout << colorCode << prefix;
        (std::cout << ... << std::forward<Args>(args));
        std::cout << "\033[0m" << std::endl;

        if (fileStream.is_open()) {
            fileStream << prefix;
            (fileStream << ... << std::forward<Args>(args));
            fileStream << std::endl;
        }
    }

    void setupConsole();
};

extern Logger defaultLogger;