
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <ctime>
#include<mutex>
#include <vector>
#include "alerts.hpp"


using namespace std;
mutex logMutex;



string getTimeStamp(){
    char returnString[100];
    struct tm * timeInfo;
    time_t timer = time(NULL);
    timeInfo = localtime(&timer);
    strftime(returnString,100,"Time Stamp: %m/%d/%Y %I:%M%p.", timeInfo);
    return returnString;

}

void logtoFile(string timestamplog, bool currentstat){
    logMutex.lock();
    fstream fs("newegg_log.txt", std::ios::app);
    if(fs.is_open()){
        if(currentstat){
            fs << timestamplog << std::boolalpha <<"Current Item status: " <<  currentstat <<  endl;
        }
        else{
            fs << timestamplog << std::boolalpha <<"Current Item status: " <<  currentstat <<  endl;
         }
    }
    else{
        cout << "File is not open!";
        return;
    }
    fs.close();
    logMutex.unlock();
}




#endif