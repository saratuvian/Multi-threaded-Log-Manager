# Multi-threaded Log Manager

This project is a multi-threaded logger system that manages user input, writes it to log files, and handles file rotation when a file exceeds a specified size limit. It also provides functionality to count occurrences of a specified character across all log files.

## Features
- Multi-threaded input and output processing using C++ threads.
- Automatic log file rotation when the current file exceeds 100 bytes.
- Directory cleaning and setup at the start of each session.
- Character counting across all log files.
- Stops running upon receiving the `exit` command from the user.

## How It Works
- **Log Creation**: Logs are stored in a directory, and a new log file is created when the current one reaches the size limit of 100 bytes.
- **Threading**: One thread handles user input, while another writes this input to log files.
- **Character Counting**: The system can count how many times a specified character appears across all log files.
- **File Rotation**: When a log file exceeds the size limit, a new file is automatically created.

## Directory Structure
- **Log Files**: The log files are stored in the specified directory, with the naming format `txt0.input`, `txt1.input`, etc.
- **Directory Preparation**: If the directory does not exist, it is created. If it already exists, it is cleared of previous log files.

## Usage

### 1. Logging Input
The logger accepts user input and writes it to files in the specified directory. Enter text from the command line, and it will be logged into files in the following format:
txt0.input txt1.input txt2.input ...
The system rotates files once the size limit is reached.

### 2. Counting Characters
You can count occurrences of a specific character across all log files using the `count(char c)` function. This scans all log files in the directory and returns the total count.

### 3. Exiting the Program
To stop logging and exit the program, enter `exit`.

## Example

```cpp
Logger logger("logs");
logger.start();
int count_a = logger.count('a');
std::cout << "Number of 'a' characters: " << count_a << std::endl

Sample Input
Hello, world!
Logging system in action
exit

Output Files
txt0.input:
Hello, world!
Logging system in action

Make sure you have a C++ compiler that supports C++17 or later.

Compile the code:
g++ -std=c++17 -pthread logger.cpp -o logger

Run the program:
./logger

Requirements
C++17 or higher
POSIX-compliant system (for threading)
