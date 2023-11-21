#include <iostream>
#include <string>
#include <stdexcept>  // for exception handling

using namespace std;

class Event {
private:
    string name;
    string date;
    string time;
    int maxSeats;
    int* seatNumbers;

    static int staticField;  // Static field

public:
    const int constantField = 42;  // Constant field

    Event() {
        name = "";
        date = "";
        time = "";
        maxSeats = 0;
        seatNumbers = nullptr;
    }

    Event(string name, string date, string time, int maxSeats) {
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

    // Copy constructor
    Event(const Event& e) {
        this->name = e.name;
        this->date = e.date;
        this->time = e.time;
        this->maxSeats = e.maxSeats;

        if (e.seatNumbers != nullptr) {
            this->seatNumbers = new int[e.maxSeats];
            for (int i = 0; i < e.maxSeats; i++) {
                this->seatNumbers[i] = e.seatNumbers[i];
            }
        }
        else {
            this->seatNumbers = nullptr;
        }
    }

    // Copy assignment operator
    Event& operator=(const Event& o) {
        if (this == &o) {
            return *this;
        }

        this->name = o.name;
        this->date = o.date;
        this->time = o.time;
        this->maxSeats = o.maxSeats;

        delete[] this->seatNumbers;

        if (o.seatNumbers != nullptr) {
            this->seatNumbers = new int[o.maxSeats];
            for (int i = 0; i < o.maxSeats; i++) {
                this->seatNumbers[i] = o.seatNumbers[i];
            }
        }
        else {
            this->seatNumbers = nullptr;
        }

        return *this;
    }

    // Destructor
    ~Event() {
        if (this->seatNumbers != nullptr) {
            delete[] this->seatNumbers;
        }
    }

    // Public methods for reading and writing values
    void setName(const string& newName) {
        this->name = newName;
    }

    void setDate(const string& newDate) {
        this->date = newDate;
    }

    void setTime(const string& newTime) {
        this->time = newTime;
    }

    void setMaxSeats(int newMaxSeats) {
        if (newMaxSeats >= 0) {
            this->maxSeats = newMaxSeats;

            // Reallocate seatNumbers if necessary
            delete[] this->seatNumbers;

            if (newMaxSeats > 0) {
                this->seatNumbers = new int[newMaxSeats];
            }
            else {
                this->seatNumbers = nullptr;
            }
        }
        else {
            throw invalid_argument("Maximum seats must be non-negative.");
        }
    }

    // Generic methods for processing/displaying attributes
    void displayEventInfo() const {
        cout << "Event Name: " << this->name << endl;
        cout << "Event Date: " << this->date << endl;
        cout << "Event Time: " << this->time << endl;
        cout << "Maximum Seats: " << this->maxSeats << endl;
    }

    void processEvent() const {
        // Perform some processing based on event attributes
        cout << "Processing Event: " << this->name << endl;
    }

    // Static field getter
    static int getStaticField() {
        return staticField;
    }

    // Static field setter
    static void setStaticField(int value) {
        staticField = value;
    }

    // Overloaded << operator for displaying Event
    friend ostream& operator<<(ostream& out, const Event& event) {
        out << "Event Name: " << event.name << endl;
        out << "Event Date: " << event.date << endl;
        out << "Event Time: " << event.time << endl;
        out << "Maximum Seats: " << event.maxSeats << endl;
        return out;
    }

    // Overloaded >> operator for input
    friend istream& operator>>(istream& in, Event& event) {
        cout << "Enter event name: ";
        getline(in, event.name);
        cout << "Enter event date: ";
        getline(in, event.date);
        cout << "Enter event time: ";
        getline(in, event.time);
        cout << "Enter maximum number of seats: ";
        in >> event.maxSeats;

        // Validate input
        if (event.maxSeats > 0) {
            event.seatNumbers = new int[event.maxSeats];
        }
        else {
            event.seatNumbers = nullptr;
        }

        return in;
    }

    // Indexing operator []
    int& operator[](int index) {
        if (index >= 0 && index < maxSeats) {
            return seatNumbers[index];
        }
        else {
            throw out_of_range("Invalid index.");
        }
    }

    // Arithmetic operators (+, -) for Event
    Event operator+(const Event& other) const {
        Event result = *this;
        result.maxSeats += other.maxSeats;
        return result;
    }

    Event operator-(const Event& other) const {
        Event result = *this;
        result.maxSeats -= other.maxSeats;
        // Ensure non-negative maxSeats
        result.maxSeats = max(0, result.maxSeats);
        return result;
    }

    // Increment (++) and Decrement (--) operators for Event
    Event& operator++() {
        // Prefix increment (++event)
        this->maxSeats++;
        return *this;
    }

    Event operator++(int) {
        // Postfix increment (event++)
        Event temp = *this;
        ++(*this);
        return temp;
    }

    Event& operator--() {
        // Prefix decrement (--event)
        // Ensure non-negative maxSeats
        this->maxSeats = max(0, this->maxSeats - 1);
        return *this;
    }

    Event operator--(int) {
        // Postfix decrement (event--)
        Event temp = *this;
        --(*this);
        return temp;
    }

    // Cast operator to string
    operator string() const {
        return "Event: " + name + " - Date: " + date + " - Time: " + time;
    }

    // Negation operator !
    bool operator!() const {
        // Event is valid if name, date, and time are not empty, and maxSeats is positive
        return name.empty() || date.empty() || time.empty() || maxSeats <= 0;
    }

    // Conditional operators (<, >, <=, >=)
    bool operator<(const Event& other) const {
        return maxSeats < other.maxSeats;
    }

    bool operator>(const Event& other) const
