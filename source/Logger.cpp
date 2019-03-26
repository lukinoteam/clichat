#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

class Logger{
public:
    void logMessage(std::string nickName, std::string message);
    void getMessage();
private:
    std::string getCurrentTime();

};

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

void Logger::logMessage(std::string nickName, std::string message){
    std::ofstream writeFile;
    writeFile.open("chat.log", std::ios::app);


    writeFile << getCurrentTime() << "\t"<< nickName << "\t" << message << std::endl;


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
        std::string nickName;
        std::string message;

        stream >> date >> time >> nickName >> message;

        std::cout << time.substr(3,7) << "\t" << nickName << ":\t" << message<< std::endl;
    }
}



