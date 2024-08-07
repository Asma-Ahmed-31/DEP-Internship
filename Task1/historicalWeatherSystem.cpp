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




class WeatherHistory {
private:
    static size_t DataHandler(void* contents, size_t size, size_t nmemb, string* buffer) {
        size_t totalSize = size * nmemb;
        buffer->append((char*)contents, totalSize);
        return totalSize;
    }

public:
    static string retrieveHistoricalData(const string& key, const string& url, const string& city, const string& day) {
        CURL* curl;
        CURLcode res;
        string responseBuffer;

        curl = curl_easy_init();
        if (curl) {
            string requestUrl = url + "?q=" + city + "&date=" + day + "&appid=" + key;
            curl_easy_setopt(curl, CURLOPT_URL, requestUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataHandler);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return responseBuffer;
    }

    static void printHistoricalData(const string& data) {
        cout << "Historical Weather Data: " << data << endl;
    }
};



int main() {
	
	// fetch and displai data for current weather...
    string apiKey = "Enter_your_API"; 
    string baseUrl = "Ehttps://open-meteo.com/en/docs";
    string location = "Islamabad";

    string weatherData = CurrentWeatherSystem::fetchWeatherData(apiKey, baseUrl, location);
    CurrentWeatherSystem::displayWeatherData(weatherData);
    
    // fetch and display data for historical weather...
    string apiToken = "Enter_your_API"; 
    string endpointUrl = "https://open-meteo.com/en/docs/historical-forecast-api";
    string cityName = "Islamabad";
    string targetDate = "2023-08-01";    // Specify the date for historical data....

    string historicalWeather = WeatherHistory::retrieveHistoricalData(apiToken, endpointUrl, cityName, targetDate);
    WeatherHistory::printHistoricalData(historicalWeather);

    return 0;
}