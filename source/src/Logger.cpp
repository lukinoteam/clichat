#include "Logger.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

Logger::Logger()
{
    //ctor
}

Logger::~Logger()
{
    //dtor
}

std::string Logger::getCurrentTime(){
    std::string time = "";

    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    time = "";
    time += std::to_string((now->tm_year + 1900));
    time += '-';
    time += std::to_string((now->tm_mon + 1));
    time += '-';
    time += std::to_string(now->tm_mday);
    time += ' ';
    time += std::to_string(now->tm_hour);
    time += ':';
    time += std::to_string(now->tm_min);
    time += ':';
    time += std::to_string(now->tm_sec);

    return time;
}

void Logger::logMessage(std::string message){
    std::ofstream writeFile;
    writeFile.open("chat.log", std::ios::app);


    writeFile << getCurrentTime() << "\t" << message << std::endl;


    writeFile.close();
}

void Logger::getMessage(){
    std::ifstream readFile;
    readFile.open("chat.log");

    std::string line;
    while(getline(readFile, line)){
        std::istringstream stream(line);
        std::string date;
        std::string time;
        std::string message;

        stream >> date >> time >> message;

        std::cout << time.substr(3,7) << "\t" << message<< std::endl;
    }
}
