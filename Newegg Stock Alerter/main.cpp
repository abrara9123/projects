
//Compile Command:  g++ main.cpp -IC:\vcpkg\installed\x64-mingw-dynamic\include -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl -o prog
// Cd commands: cd /c/Users/fiora/Documents/c++/TestFodleroristanlls
#include "checker.hpp"
#include <vector>
#include <thread>
using namespace std;


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