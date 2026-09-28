// C++ program to implement a basic logging system.

#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime> 
//#pragma once

using namespace std;

// Enum to represent log levels
enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
private:
    bool enable;
    ofstream logFile; // File stream for the log file
	LogLevel currentLevel; // Default log level
    bool displayLog; 
    
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
    Logger(const string& filename, LogLevel setLevel, bool enable, bool displayLog)
    {
        logFile.open(filename, ios::app);
        if (!logFile.is_open()) {
            cerr << "Error opening log file." << endl;
        }
        this->enable = enable;
		this->displayLog = displayLog;
		setLogLevel(setLevel);
    }

    // Destructor: Closes the log file
    ~Logger() { logFile.close(); }

    // Logs a message with a given log level
    pair<LogLevel, string> writelog(LogLevel level, const string& message)
    {   
        if (this->enable) {
            // Create log entry
            ostringstream logEntry;

            logEntry << "\n" << getTime() <<" [" << levelToString(level) << "]: " << message << endl;


            // Output to log file
            if (logFile.is_open()) {
                logFile << logEntry.str();
                logFile
                    .flush(); // Ensure immediate write to file
            }
			return make_pair(level, logEntry.str());
        }
    }

    void dispLog(pair<LogLevel, string> display){
		LogLevel level = display.first;
		string message = display.second;

        if(level >= this->currentLevel) {
            cout << message;
		}
    }


    void log(LogLevel level, const string& message) {
        if (level < this->currentLevel) {
            return;
        }
        pair<LogLevel, string> logEntry = writelog(level, message);
        if (this->displayLog) {
        dispLog(logEntry);
        }
	}




	//Setters:
    
    void setLogLevel(LogLevel level) {
        this->currentLevel = level;
	}

    //Geters:

    string getTime() {
        time_t rawtime;
        struct tm datetime;
        char buffer[30];
        time(&rawtime);
        localtime_s(&datetime, &rawtime);

        strftime(buffer, sizeof(buffer), "%H:%M:%S", &datetime);
        return string(buffer);
    }
};
