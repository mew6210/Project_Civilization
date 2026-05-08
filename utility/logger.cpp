#include "Logger.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

Logger::Logger(const std::string& filename) {
    fileStream.open(filename, std::ios::app);
    setupConsole();
}

Logger::~Logger() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

void Logger::setupConsole() {
    //Enabling Virtual Terminal Processing
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= 0x0004;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

//Global variable
Logger defaultLogger = Logger("log.txt");