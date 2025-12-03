// C++ program to implement a basic logging system.

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Enum to represent log levels
enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
private:
    bool enable;
    ofstream logFile; // File stream for the log file

    
    string levelToString(LogLevel level)
    {
        switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }
public:
    // Constructor: Opens the log file in append mode
    Logger(const string& filename, bool enable)
    {
        logFile.open(filename, ios::app);
        if (!logFile.is_open()) {
            cerr << "Error opening log file." << endl;
        }
        this->enable = enable;
    }

    // Destructor: Closes the log file
    ~Logger() { logFile.close(); }

    // Logs a message with a given log level
    void log(LogLevel level, const string& message)
    {   
        if (this->enable) {
            // Create log entry
            ostringstream logEntry;

            logEntry << levelToString(level) << ": " << message << endl;

            // Output to console
            cout << logEntry.str();

            // Output to log file
            if (logFile.is_open()) {
                logFile << logEntry.str();
                logFile
                    .flush(); // Ensure immediate write to file
            }
        }
    }
};
