
//Compile Command:  g++ main.cpp -IC:\vcpkg\installed\x64-mingw-dynamic\include -LC:\vcpkg\installed\x64-mingw-dynamic\lib -lcurl -o prog

#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

// When curl downloads data it comes in chunks, and you need a function that says "whenever you get a chunk, put it here.
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(){
CURL* curl = curl_easy_init();

if(curl != NULL){
    //curl_easy_setopt is the settings function and this lets us configure the settings before we call it
    // Takes 3 arguments  - (curl object, the setting, value we set it to )
    string response;
    //CURLOPT_URL -  tells the prgram wahat url to go fetch
    // CURLOPT_WRITEFUNCTION - the data from the url will come in chunks, and then we want the Callback
    //function to  write it properly
    // CURLOPT_WRITEDATA- tells it where to put the data in so every chunck gets put itnot the string
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.newegg.com/zotac-rtx-5090-solid-oc-geforce-rtx-5090-32gb-graphics-card-triple-fans/p/N82E16814500598");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
    // struct curl_slist* headers = NULL;
    // headers = curl_slist_append(headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    // headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.5");
    // headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
    // headers = curl_slist_append(headers, "Connection: keep-alive");
//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

 /*
    curl_easy_perform is the moment everything happens:
curl connects to the server
downloads the page chunk by chunk
calls your WriteCallback for each chunk as it arrives
each chunk gets appended to response
when done, curl_easy_perform returns
*/

    // CURLcode res = curl_easy_perform(curl);
    // curl_slist_free_all(headers);
// cout << "Status: " << curl_easy_strerror(res) << endl;

// long http_code = 0;
// curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
// cout << "HTTP code: " << http_code << endl;

//cout << response.substr(0,500) << endl;

curl_easy_perform(curl);
if(response.find("IsAvailableForRegion\":true") != string::npos){
    cout << "Item is in stock" << endl;
}
else{
    cout << "Item is not in stock" << endl;
}
    curl_easy_cleanup(curl);
}




}