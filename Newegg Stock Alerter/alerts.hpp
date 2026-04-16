#ifndef ALERTS_HPP
#define ALERTS_HPP

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
using namespace std;

mutex alertMutex;


void AlertMutex(string checkurl){
    alertMutex.lock();
        Beep(1000,1000);
       string command = "start cmd /k echo Item is in stock! Go buy it on Newegg! Link: " + checkurl;
     system(command.c_str());
    alertMutex.unlock();
}

#endif