#ifndef H_LOGGER_H
#define H_LOGGER_H
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <atomic>

class Logger {
private:
    std::string directory_;
    std::string current_filename_;
    std::queue<std::string> buffer_;
    std::atomic<bool> exit_flag_;
    void getLinesFromKeyboard();
    void writeLinesToFiles();
    std::string getNextFilename();
    void createOrCleanDirectory();

public:
    Logger(const std::string& directory);
    void start();
    void log(const std::string& input);
    int count(char c);
};

#endif // H_LOGGER_H
