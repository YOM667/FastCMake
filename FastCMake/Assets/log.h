#pragma once

// User can use default config or use marco define LOGGER_CONFIG
// The marco accept a header file's in your project, you need in the config file change config
#ifdef LOGGER_CONFIG
#include LOGGER_CONFIG
#endif

// it is ok that you can in your source file define marco about logger
#ifndef LOGGER_OUTPUT_FORMAT
#define LOGGER_OUTPUT_FORMAT "(%s) %s [%s %d]: "
#endif

#ifndef LOGGER_TIME_FORMAT
#define LOGGER_TIME_FORMAT "%Y-%m-%d %H:%M:%S"
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdarg>

#include "utility.h"

using namespace std;

namespace youm::utility
{
    //The logger marco function to output and restore in log file
    #define debug(message, ...) youm::utility::Logger::instance()->log(youm::utility::Logger::LEVEL_DEBUG,__FILE__,__LINE__, message, ##__VA_ARGS__)

    #define info(message, ...) youm::utility::Logger::instance()->log(youm::utility::Logger::LEVEL_INFO,__FILE__,__LINE__, message, ##__VA_ARGS__)

    #define error(message, ...) youm::utility::Logger::instance()->log(youm::utility::Logger::LEVEL_ERROR,__FILE__,__LINE__, message, ##__VA_ARGS__)

    #define warning(message, ...) youm::utility::Logger::instance()->log(youm::utility::Logger::LEVEL_WARN,__FILE__,__LINE__, message, ##__VA_ARGS__)

    #define fatal(message, ...) youm::utility::Logger::instance()->log(youm::utility::Logger::LEVEL_FATAL,__FILE__,__LINE__, message, ##__VA_ARGS__)

    class Logger
    {
    public:
        //LOG LEVEL
        enum Level
        {
            LEVEL_DEBUG = 0,
            LEVEL_INFO,
            LEVEL_WARN,
            LEVEL_ERROR,
            LEVEL_FATAL,
            LEVEL_COUNT
        };
        Logger();
        ~Logger();
        //THE FUNCTION CAN GET A LOGGER INSTANCE JUST ONLY HAVE ONE LOGGER INSTANCE
        static Logger* instance();
        //Open log file
        //if not exist, the function will create a new file
        void open();
        //Close log file
        void close();
        //level   : want to output log level, by marco select
        //file    : need a __FILE__ marco, it can replace to file's path in the system
        //file    : need a __LINE__ marco, it can replace to 'invoke line' in some files
        //message : the message you want to output in consoles and log file
        //...     : this is a variable arguments that can format output message such as printf("%s",str)
        void log(Level level, const char* file, int line, const char* message, ...);
    private:
        //the logger output log file path
        string localFile;
        //output stream, to write log
        ofstream outStream;
        //levels string and enum shift
        static const char* levels[LEVEL_COUNT];
        //log instance
        static Logger* logInstance;
    };
}