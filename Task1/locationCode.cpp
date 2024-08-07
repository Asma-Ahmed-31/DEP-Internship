#include<iostream>
#include<string>
using namespace std;

const int max_locations = 90; // Maximum number of locations

class Location {
public:
    string name;
    double latitude;
    double longitude;

    void set_location(const string& n, double lat, double lon) {
        name = n;
        latitude = lat;
        longitude = lon;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
    }
};

Location locations[max_locations];
int location_count = 0;

void add_location(const string& name, double latitude, double longitude) {
    if (location_count < max_locations) {
        locations[location_count].set_location(name, latitude, longitude);
        location_count++;
    } else {
        cout << "Cannot add more locations. Our limit is finished" << endl;
    }
}

void remove_location(const string& name) {
    for (int i = 0; i < location_count; i++) {
        if (locations[i].name == name) {
            for (int j = i; j < location_count - 1; j++) {
                locations[j] = locations[j + 1];
            }
            location_count--;
            cout << "Location " << name << " removed." << endl;
            return;
        }
    }
    cout << "Location not found." << endl;
}

void list_locations() {
    if (location_count == 0) {
        cout << "No locations" << endl;
    } else {
        for (int i = 0; i < location_count; i++) {
            locations[i].display();
            cout << "--------------------" << endl;
        }
    }
}

int main() {
    add_location("Nathia_Gali", 34.0668, 73.3908);
    add_location("Murree", 33.9070, 73.3943);
    add_location("Hunza", 36.3167, 74.6500);

    cout << "All Locations:" << endl;
    list_locations();

    cout << "Removing Murree:" << endl;
    remove_location("Murree");

    cout << "All Locations after removal:" << endl;
    list_locations();

    return 0;
}
