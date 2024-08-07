#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

class CurrentWeatherSystem {
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t totalSize = size * nmemb;
        s->append((char*)contents, totalSize);
        return totalSize;
    }

public:
    static string fetchWeatherData(const string& apiKey, const string& baseUrl, const string& location) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            string url = baseUrl + "?q=" + location + "&appid=" + apiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    static void displayWeatherData(const string& data) {
        cout << "Weather Data: " << data << endl;
    }
};

int main() {
    string apiKey = "Enter_your_API"; 
    string baseUrl = "https://open-meteo.com/en/docs";
    string location = "Islamabad";

    string weatherData = CurrentWeatherSystem::fetchWeatherData(apiKey, baseUrl, location);
    CurrentWeatherSystem::displayWeatherData(weatherData);

    return 0;
}

