// the bonus part (email) is commented in a separate program after this program ends as it uses certain library that could result in errors if not installed

// program without email bonus
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
        cout << "Guest: " << name << ", Contact: " << contact << ", Iftar Date: " << iftar_date << endl;
    }

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
        guest_list = new Guest *[capacity];
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
                cout << "Reminder sent to " << guest_list[i]->get_name() << ": Your Iftar invitation is on " << date
                     << "!" << endl;
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

    void remove_guest(string name) {
        for (int i = 0; i < size; i++) {
            if (guest_list[i]->get_name() == name) {
                delete guest_list[i]; // free memory
                for (int j = i; j < size - 1; j++) {
                    guest_list[j] = guest_list[j + 1]; // shift guests
                }
                size--; // reduce the number of guests
                cout << "Guest '" << name << "' removed successfully." << endl;
                return;
            }
        }
        cout << "Guest '" << name << "' not found!" << endl;
    }

};

int main() {
    IftarManager manager;
    Guest *guest1 = new Guest("Aisha", "aisha@example.com", "2025-03-15");
    Guest *guest2 = new Guest("Omar", "omar@example.com", "2025-03-18");
    Guest *guest3 = new Guest("Zainab", "zainab@example.com", "2025-03-20");
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
    cout << endl << "Removing Aisha ..." << endl;
    manager.remove_guest("Aisha");
    cout << endl << "After removing Aisha: " << endl;
    manager.display_all_guests();
    return 0;
}


// program containing email bonus
/*
#include <iostream>
#include <curl/curl.h>

using namespace std;

class Guest {
private:
    string name;
    string contact;
    string iftar_date;
public:
    Guest(string n, string c, string d) : name(n), contact(c), iftar_date(d) {}

    void display_guest() {
        cout << "Guest: " << name << ", Contact: " << contact << ", Iftar Date: " << iftar_date << endl;
    }

    string get_name() {
        return name;
    }

    string get_iftar_date() {
        return iftar_date;
    }

    void update_invitation(string new_date) {
        iftar_date = new_date;
    }

    // Getter for the guest's contact (email)
    string get_contact() {
        return contact;
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
        guest_list = new Guest *[capacity];
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
                cout << "Reminder sent to " << guest_list[i]->get_name() << ": Your Iftar invitation is on " << date
                     << "!" << endl;
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

    void remove_guest(string name) {
        for (int i = 0; i < size; i++) {
            if (guest_list[i]->get_name() == name) {
                delete guest_list[i]; // free memory
                for (int j = i; j < size - 1; j++) {
                    guest_list[j] = guest_list[j + 1]; // shift guests
                }
                size--; // reduce the number of guests
                cout << "Guest '" << name << "' removed successfully." << endl;
                return;
            }
        }
        cout << "Guest '" << name << "' not found!" << endl;
    }

    Guest **get_guest_list() {
        return guest_list;
    }

    int get_size() {
        return size;
    }


    void send_email(const string &email, const string &name, const string &date) {
        CURL *curl; // This is a pointer to a CURL object
        CURLcode res; //enum type defined by libcurl that represents various possible return codes

        struct curl_slist *guests = NULL;
        const char *from = "your-email@example.com"; // Your email
        string to = email; // Recipient email (could be guest email)
        const char *smtp_server = "smtp://smtp.example.com"; // SMTP server address
        const int smtp_port = 587; // SMTP port (usually 587 for TLS)
        const char *username = "your-email@example.com"; // SMTP username (your email)
        const char *password = "your-email-password"; // SMTP password (your email password)

        string content = "Iftar Invitation Reminder";
        string body = "Dear " + name + ",\n\nYour Iftar invitation is scheduled for " + date +
                      ".\n\nBest regards,\nIftar Manager";

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl) {
            // Set SMTP server
            curl_easy_setopt(curl, CURLOPT_URL, smtp_server);
            curl_easy_setopt(curl, CURLOPT_PORT, smtp_port);

            // Authentication
            curl_easy_setopt(curl, CURLOPT_USERNAME, username);
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

            // Email details
            curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);
            guests = curl_slist_append(guests, to.c_str());
            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, guests);

            // Set headers, including subject
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, ("Subject: " + content).c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Email body
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

            // Perform the request (sending the email)
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                cerr << "Email sending failed: " << curl_easy_strerror(res) << endl;
            } else {
                cout << "Email sent successfully to " << name << endl;
            }

            // Cleanup
            curl_slist_free_all(headers);
            curl_slist_free_all(guests);
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

    }
};

int main() {
    IftarManager manager;
    Guest *guest1 = new Guest("Aisha", "aisha@example.com", "2025-03-15");
    Guest *guest2 = new Guest("Omar", "omar@example.com", "2025-03-18");
    Guest *guest3 = new Guest("Zainab", "zainab@example.com", "2025-03-20");
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
    string reminder_date = "2025-03-15";

    Guest **guests = manager.get_guest_list();
    int guest_count = manager.get_size();
    for (int i = 0; i < guest_count; i++) {
        if (guests[i]->get_iftar_date() == reminder_date) {
            manager.send_email(guests[i]->get_name(), guests[i]->get_contact(), guests[i]->get_iftar_date());
        }
    }

    manager.sort_guest_list();
    cout << endl << "Sorted Guest List:" << endl;
    manager.display_all_guests();
    cout << endl << "Removing Aisha ..." << endl;
    manager.remove_guest("Aisha");
    cout << endl << "After removing Aisha: " << endl;
    manager.display_all_guests();
    return 0;
}

 */
