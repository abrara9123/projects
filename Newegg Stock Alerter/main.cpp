
//Compile Command:  g++ main.cpp -IC:\vcpkg\installed\x64-mingw-dynamic\include -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl -o prog
// Cd commands: cd /c/Users/fiora/Documents/c++/TestFodleroristanlls
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
mutex logMutex;
mutex urlcheck;

void AlertMutex(){
    alertMutex.lock();
        Beep(1000,1000);
        system("start cmd /k echo Item is in stock! Go buy it on Newegg!");
    alertMutex.unlock();
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}
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

int main(){
    vector<string> url(3);
    url[0] = "https://www.newegg.com/gigabyte-windforce-gv-n507twf3oc-16gd-geforce-rtx-5070-ti-16gb-graphics-card-triple-fans/p/N82E16814932771";
    url[1] = "https://www.newegg.com/corsair-rmx-series-atx-3-1-compatible-1000-w-cybenetics-gold-power-supply-black-rm1000e/p/N82E16817139337?Item=N82E16817139337";
    url[2] = "https://www.newegg.com/amd-ryzen-7-5000-series-ryzen-7-5800xt-vermeer-socket-am4-desktop-cpu-processor/p/N82E16819113846?Item=9SIC4Z7KT62169";
    thread t1(checkItem, url[0]);
    thread t2(checkItem, url[1]);
    thread t3(checkItem, url[2]);
    
    t1.join();
    t2.join();
    t3.join();


    return 0;
}
