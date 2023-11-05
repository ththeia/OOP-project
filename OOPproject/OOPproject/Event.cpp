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
    Event()
        : maxSeats(0), seatNumbers(nullptr) {}

    Event(const string& name, const string& date, const string& time, int maxSeats)
        : name(name), date(date), time(time), maxSeats(maxSeats) {
        this->seatNumbers = new int[maxSeats];
    }

    ~Event() {
        delete[] this->seatNumbers;
    }

    const string& getName() const {
        return this->name;
    }

    const string& getDate() const {
        return this->date;
    }

    const string& getTime() const {
        return this->time;
    }

    int getMaxSeats() const {
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
