#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

class Logger
{
    public:
        Logger();
        virtual ~Logger();
        void logMessage(std::string message);
        void getMessage();
    private:
        std::string getCurrentTime();
};

#endif // LOGGER_H
