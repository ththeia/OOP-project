#include <iostream>
#include <string>

using namespace std;

class Event {
private:
    string name;
    string date;
    string time;
    int maxSeats;
    int* seatNumbers;

public:
    Event() {
        name = "";
        date = "";
        time = "";
        maxSeats = 0;
        seatNumbers = nullptr;
    }

    Event(const string& name, const string& date, const string& time, int maxSeats) {
        this->name = name;
        this->date = date;
        this->time = time;
        this->maxSeats = maxSeats;

        if (maxSeats > 0) {
            this->seatNumbers = new int[maxSeats];
        }
        else {
            this->seatNumbers = nullptr;
        }
    }


    ~Event() {
        if (this->seatNumbers != nullptr) {
            delete[] this->seatNumbers;
        }
    }
    const string& getName()  {
        return this->name;
    }

    const string& getDate()  {
        return this->date;
    }

    const string& getTime() {
        return this->time;
    }

    int getMaxSeats()  {
        return this->maxSeats;
    }

    int* getSeatNumbers() {
        return this->seatNumbers;
    }

    bool isValid() const {
        return !this->name.empty() && !this->date.empty() && !this->time.empty() && this->maxSeats > 0;
    }

    friend istream& operator>>(istream& in, Event& event) {
        cout << "Enter event name: ";
        getline(in, event.name);
        cout << "Enter event date: ";
        getline(in, event.date);
        cout << "Enter event time: ";
        getline(in, event.time);
        cout << "Enter maximum number of seats: ";
        in >> event.maxSeats;

        if (event.maxSeats > 0) {
            event.seatNumbers = new int[event.maxSeats];
        }

        return in;
    }

    friend ostream& operator<<(ostream& out, const Event& event) {
        out << "Event Name: " << event.name << endl;
        out << "Event Date: " << event.date << endl;
        out << "Event Time: " << event.time << endl;
        out << "Maximum Seats: " << event.maxSeats << endl;
        return out;
    }
};


    int main() {

        Event event1;    
        cin >> event1;

        
        if (event1.isValid()) {
            cout << "Event Details:\n" << event1;
        }
        else {
            cout << "Invalid event details entered.\n";
        }
        Event event2("Event 2", "2023-11-05", "15:00", 100);
        cout << "Event Details:\n" << event2;


    };