#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>

using namespace std;
namespace fs = std::filesystem;

enum typelog
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

struct structlog
{
    bool headers = true;
    typelog level = DEBUG;
    string logFileName = "log/log.log"; // default log path
};

extern structlog LOGCFG;
structlog LOGCFG;

// USAGE: LOG(INFO) << "This is a message";
// OUTPUT: 2023-01-01 12:34:56 [INFO] This is a message

class LOG
{
  public:
    LOG()
    {
    }
    LOG(typelog type)
    {
        msglevel = type;
        if (LOGCFG.headers)
        {
            lock_guard<mutex> lock(logMutex); // Lock before printing headers
            createLogFile();
            logStream.open(getLogFilePath(), ios::app);
            logStream << getCurrentDateTime() << " "
                      << "[" << getLabel(type) << "] ";
        }
    }
    ~LOG()
    {
        if (opened)
        {
            lock_guard<mutex> lock(logMutex); // Lock before printing newline
            logStream << endl;
            logStream.close();
        }
    }
    template <class T> LOG &operator<<(const T &msg)
    {
        if (msglevel >= LOGCFG.level)
        {
            lock_guard<mutex> lock(logMutex); // Lock before printing the message
            logStream << msg;
            opened = true;
        }
        return *this;
    }

  private:
    bool opened = false;
    typelog msglevel = DEBUG;
    ofstream logStream;
    inline string getLabel(typelog type)
    {
        string label;
        switch (type)
        {
        case DEBUG:
            label = "DEBUG";
            break;
        case INFO:
            label = "INFO";
            break;
        case WARNING:
            label = "WARNING";
            break;
        case ERROR:
            label = "ERROR";
            break;
        }
        return label;
    }

    string getLogFilePath()
    {
        if (!LOGCFG.logFileName.empty())
        {
            return LOGCFG.logFileName;
        }
        else
        {
            return "log/log.log";
        }
    }

    void createLogFile()
    {
        if (!fs::exists("log"))
        {
            fs::create_directory("log");
        }
        if (!fs::exists(getLogFilePath()))
        {
            ofstream file(getLogFilePath());
            file.close();
        }
    }

    string getCurrentDateTime()
    {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm localTime;
        localtime_s(&localTime, &now);

        stringstream ss;
        ss << put_time(&localTime, "%Y-%m-%d %X");
        return ss.str();
    }

    static mutex logMutex; // Static mutex shared by all instances
};

mutex LOG::logMutex;

#endif
