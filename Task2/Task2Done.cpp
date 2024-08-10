#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Contact {
public:
    int serial_number;
    string person_name;
    string person_contact;

    void display_contact() const {  
        cout << "Serial Number: " << serial_number << ", Name: " << person_name << ", Contact: " << person_contact << endl;
    }
};

vector<Contact> contacts;

void add_contact() {
    Contact new_contact;
    cout << "Enter the serial number of new contact: ";
    cin >> new_contact.serial_number;
    cout << "Enter the person name: ";
    cin.ignore();  
    getline(cin, new_contact.person_name);
    cout << "Enter the contact number of the person: ";
    cin >> new_contact.person_contact;
    contacts.push_back(new_contact);
    cout << "Contact added successfully!" << endl;
}

void view_contacts() {
    if (contacts.empty()) {
        cout << "No contacts available." << endl;
    } else {
        for (const auto& contact : contacts) {
            contact.display_contact();  
        }
    }
}
void delete_contact() {
    if (contacts.empty()) {
        cout << "No contacts to delete." << endl;
        return;
    }

    int index;
    cout << "Enter the number of the contact to delete: ";
    while (!(cin >> index) || index < 1 || index > contacts.size()) {
        
        cout << "Invalid contact number. Please enter a valid number: ";
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully!" << endl;
}

int main() {
    int choice;

    do {
        cout << "Contact Management System"<<endl;
        cout << "1. Add Contact"<<endl;
        cout << "2. View Contacts"<<endl;
        cout << "3. Delete Contact"<<endl;
        cout << "4. Exit" <<endl;
        cout << "Enter your choice: ";
        while(!(cin>>choice) || choice<1 || choice>4){
            cout<<"wrong input.Please enter anumber between 1 and 4: "<<endl;
        }
        cin.ignore();

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                view_contacts();
                break;
            case 3:
                delete_contact();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

return 0;
}