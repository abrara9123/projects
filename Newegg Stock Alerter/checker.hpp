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
#include "logger.hpp"
using namespace std;

string getTimeStamp();
void logtoFile(string timestamplog, bool currentstat);

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}




void checkItem(string checkUrl){
CURL* curl = curl_easy_init();

if(curl != NULL){
 
    string response;
    bool currentstatus = false;
    bool prevstatus = false;
  
    curl_easy_setopt(curl, CURLOPT_URL, checkUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");

while(true){
curl_easy_perform(curl);

if(response.find("IsAvailableForRegion\":true") != string::npos){
   
    currentstatus = true;
}
else{
    
    currentstatus = false;
    
}

if(currentstatus != prevstatus){
    if(currentstatus){
    AlertMutex();
    logtoFile(getTimeStamp(),currentstatus);
    }
    else{
        
        logtoFile(getTimeStamp(),currentstatus);
    }
    prevstatus = currentstatus;
}
this_thread::sleep_for(chrono::seconds(60));
    
}
curl_easy_cleanup(curl);

}

}
