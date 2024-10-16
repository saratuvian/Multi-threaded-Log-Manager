#include "logger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

Logger::Logger(const std::string& directory) : directory_(directory), exit_flag_(false) {
    createOrCleanDirectory();
    current_filename_ = getNextFilename();
}

void Logger::createOrCleanDirectory() {
    if (!fs::exists(directory_)) {
        if (!fs::create_directory(directory_)) {
            std::cerr << "Can't prepare the directory" << std::endl;
            return;
        }
    }
    else {
        for (const auto& entry : fs::directory_iterator(directory_)) {
            if (!fs::remove(entry.path())) {
                std::cerr << "Can't prepare the directory" << std::endl;
                return;
            }
        }
    }
}

std::string Logger::getNextFilename() {
    static int file_index = 0;
    return directory_ + "/txt" + std::to_string(file_index++) + ".input";
}

void Logger::log(const std::string& input) {
    std::ifstream infile(current_filename_, std::ios::in | std::ios::ate);
    int current_size = infile.tellg();
    infile.close();

    if (current_size + input.size() + 1 > 100) {
        current_filename_ = getNextFilename();
        current_size = 0;
    }

    std::ofstream outfile(current_filename_, std::ios::app);
    if (!outfile.is_open()) {
        std::cerr << "Can't open the file " << current_filename_ << std::endl;
        return;
    }

    outfile << input << '\n';
    outfile.close();
}

int Logger::count(char c) {
    int total_count = 0;

    for (const auto& entry : fs::directory_iterator(directory_)) {
        std::ifstream infile(entry.path());
        if (!infile.is_open()) {
            std::cerr << "Can't open the file " << entry.path().filename() << std::endl;
            continue;
        }

        char ch;
        while (infile.get(ch)) {
            if (ch == c) {
                ++total_count;
            }
        }
        infile.close();
    }

    return total_count;
}

void Logger::getLinesFromKeyboard() {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line == "exit") {
            exit_flag_ = true;
            break;
        }
        if (line.size() <= 100) {
            buffer_.push(line);
        }
    }
}

void Logger::writeLinesToFiles() {
    while (!exit_flag_ || !buffer_.empty()) {
        if (!buffer_.empty()) {
            std::string line = buffer_.front();
            buffer_.pop();
            log(line);
        }
    }
}

void Logger::start() {
    std::thread input_thread(&Logger::getLinesFromKeyboard, this);
    std::thread output_thread(&Logger::writeLinesToFiles, this);

    input_thread.join();
    output_thread.join();
}
