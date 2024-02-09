#include "Event.h"
#include <string>
#include <cstring>

#include <iomanip>
#include "validate.h"

//#include "validate.cc"

using namespace std;

/*
Event must have the following methods:


The string must contain an event, in one of the five HW3 formats. Initialize the Event to that date. 
Throw an explanatory runtime_error, including the entire bad date argument string, if the date is bad in any way, 
syntactically (e.g., 12-cucumber) or semantically (e.g., 2020-02-30).
*/

/// here i need to make a function that takes in string and cstring and then returns a time object then sets int values according to
tm validate(string str) {
    return date_parser(str);
}




// Event(C string)
Event::Event(const char *str) {
    tm t{};

    inputString.assign(str, str + strlen(str));
    t = validate(inputString);

    _year = t.tm_year + 1900;
    _month = t.tm_mon + 1;
    _day = t.tm_mday;
}

// Event(C++ string)
Event::Event(string str) {
    tm t{};
    inputString = str;

    t = validate(inputString);

    _year = t.tm_year + 1900;
    _month = t.tm_mon + 1;
    _day = t.tm_mday;
}

// Copy ctor
Event::Event(const Event &rhs) {
    inputString = rhs.inputString;
    _year = rhs._year;
    _month = rhs._month;
    _day = rhs._day;
}

//change this so it creates a string and concat the ints then stoi them before return
int Event::date_index() const{
    string index;
    //index + to_string(_year) + to_string(_month) + to_string(_day);
    return stoi(index + to_string(_year) + to_string(_month) + to_string(_day));
    //return(1);
}

/*
Assignment operator
Copy the information from the other Event.
*/
Event &Event::operator=(const Event &other) {
    _year = other._year;
    _month = other._month;
    _day = other._day;

    return *this;
}

/*
Dtor
Destroy.
*/
Event::~Event() {}

/*
.set(int year, int month, int day)
Set the date for this Event to that date. Throw a runtime_error, containing the bad data, and leave the object unchanged, if the date is bad in any way. .set(2023,4,4) would set the date to today.
*/
void Event::set(int new_year, int new_month, int new_day) {
    _year = new_year;
    _month = new_month;
    _day = new_day;
}

// year getter
int Event::year() const{
    return _year;
}

// month getter
int Event::month() const{
    return _month;
}

// day getter
int Event::day() const{
    return _day;
}



/*
ostream << Event
Write this Event to the ostream in YYYY-MM-DD format. Write exactly ten characters–nothing else.
*/
ostream &operator<<(std::ostream &os, Event &e) {
    os << std::setw(4) << std::setfill('0') << e.year() << "-"
       << std::setw(2) << std::setfill('0') << e.month() << "-"
       << std::setw(2) << std::setfill('0') << e.day()
       << std::setfill(' ');
    return os;
}

bool operator<(const Event &lhs, const Event &rhs) {
    return lhs.date_index() < rhs.date_index();
}

bool operator>(const Event &lhs, const Event &rhs) {
    return lhs.date_index() > rhs.date_index();
}

bool operator==(const Event& lhs, const Event& rhs) {
    return (lhs.year() == rhs.year()) && (lhs.month() == rhs.month()) && (lhs.day() == rhs.day());
}
bool operator!=(const Event& lhs, const Event& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Event& lhs, const Event& rhs) {
    return lhs.date_index() <= rhs.date_index();
}

bool operator>=(const Event& lhs, const Event& rhs) {
    return lhs.date_index() >= rhs.date_index();
}

string Event::fmt(const std::string format) const {
    std::tm t;
    std::memset(&t, 0, sizeof(t));
    t.tm_year = _year - 1900;
    t.tm_mon = _month - 1;
    t.tm_mday = _day;

    char buffer[1024];
    std::size_t len = std::strftime(buffer, sizeof(buffer), format.c_str(), &t);
    return string(buffer, len);
}

string Event::fmt() const {
    return std::to_string(reinterpret_cast<std::uintptr_t>(this));
}