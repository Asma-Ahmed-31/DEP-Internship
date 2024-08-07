#include <iostream>
using namespace std;

const int max_locations = 90; // Maximum number of locations

class WeatherVariable {
public:
    double temperature = 0.0;
    double wind_speed = 0.0;

    void set_weather(double temp, double wind) {
        temperature = temp;
        wind_speed = wind;
    }

    void display_weather() const {
        cout << "Temperature: " << temperature << "°C" << endl;
        cout << "Wind Speed: " << wind_speed << " km/h" << endl;
    }
};

WeatherVariable weather_data[max_locations];
int weather_count = 0;

void add_weather(double temperature, double wind_speed) {
    if (weather_count < max_locations) {
        weather_data[weather_count].set_weather(temperature, wind_speed);
        weather_count++;
    } else {
        cout << "Cannot add more weather data." << endl;
    }
}

void list_weather() {
    if (weather_count == 0) {
        cout << "No weather data available." << endl;
    } else {
        for (int i = 0; i < weather_count; i++) {
            weather_data[i].display_weather();
            cout << "--------------------" << endl;
        }
    }
}

int main() {
    add_weather(25.0, 10.0);
    add_weather(22.5, 12.5);

    cout << "The list of weather variables:" << endl;
    list_weather();

    return 0;
}