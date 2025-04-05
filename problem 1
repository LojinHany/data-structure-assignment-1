#include <iostream>
using namespace std;

class Guest {
private:
    string name;
    string contact;
    string iftar_date;
public:
    Guest(string n, string c, string d) : name(n), contact(c), iftar_date(d) {}
    void display_guest() {
        cout << "Guest: " << name << ", Contact: " << contact << ", Iftar Date: " << iftar_date << endl;}
    string get_name() {
        return name;
    }
    string get_iftar_date() {
        return iftar_date;
    }
    void update_invitation(string new_date) {
        iftar_date = new_date;
    }
};

class IftarManager {
private:
    Guest **guest_list;
    int size;
    int capacity;
public:
    IftarManager(int x = 10) {
        size = 0;
        capacity = x;
        guest_list = new Guest*[capacity];
    }
    ~IftarManager() {
        for (int i = 0; i < size; i++)
            delete guest_list[i];
        delete[] guest_list;
    }
    void add_guest(Guest *guest) {
        if (size < capacity) {
            guest_list[size++] = guest;
        } else {
            cout << "Unable to add guest as guest list is full" << endl;
        }
    }
    
    void display_all_guests() {
        for (int i = 0; i < size; i++) {
            guest_list[i]->display_guest();
        }
    }
    
    void update_guest_invitation(string name, string new_date) {
        for (int i = 0; i < size; i++) {
            if (guest_list[i]->get_name() == name) {
                guest_list[i]->update_invitation(new_date);
                cout << "Updating invitation for " << name << endl;
                return;
            }
        }
        cout << "Guest not found!" << endl;
    }

    void send_reminders(string date) {
        cout << "Sending reminders..." << endl;
        for (int i = 0; i < size; i++) {
            if (guest_list[i]->get_iftar_date() == date) {
                cout << "Reminder sent to " << guest_list[i]->get_name() << ": Your Iftar invitation is on " << date << "!" << endl;
            }
        }
    }
    
    void sort_guest_list() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (guest_list[j]->get_iftar_date() > guest_list[j + 1]->get_iftar_date()) {
                    swap(guest_list[j], guest_list[j + 1]);
                }
            }
        }
    }
};

int main() {
    IftarManager manager;
    Guest* guest1 = new Guest("Aisha", "aisha@example.com", "2025-03-15");
    Guest* guest2 = new Guest("Omar", "omar@example.com", "2025-03-18");
    Guest* guest3 = new Guest("Zainab", "zainab@example.com", "2025-03-20");
    manager.add_guest(guest1);
    manager.add_guest(guest2);
    manager.add_guest(guest3);
    manager.display_all_guests();
    cout << endl;
    manager.update_guest_invitation("Omar", "2025-03-15");
    cout << endl;
    manager.display_all_guests();
    cout << endl;
    manager.send_reminders("2025-03-15");
    manager.sort_guest_list();
    cout << endl << "Sorted Guest List:" << endl;
    manager.display_all_guests();
    return 0;
}
