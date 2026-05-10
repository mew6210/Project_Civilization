#include "Logger.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

Logger::Logger(const std::string& path) {
    std::filesystem::path logPath(path);
    if (logPath.has_parent_path()) {
        std::filesystem::create_directories(logPath.parent_path());
    }

    fileStream.open(path, std::ios::app);

    //Checking if terminal supports colors
    useColors = setupConsole();
}

Logger::~Logger() {
    if (fileStream.is_open()) fileStream.close();
}

bool Logger::setupConsole() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return false;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return false; //Returns false if colors can't be turned on
    }
    return true;
#else
    //For Linux/MacOS if terminal is TTY
    return isatty(STDOUT_FILENO);
#endif
}

//Global variable
Logger defaultLogger = Logger("logs/log.txt");