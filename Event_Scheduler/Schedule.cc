#include "Schedule.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Event.h"

// #include "validate.cc"

using namespace std;

/*
Schedule()
Create a Schedule containing no Events.
*/
Schedule::Schedule() {
    event_set = {};
}

/*
Schedule(istream)
Read Events from the given stream. All the requirements of .read() apply.
*/
Schedule::Schedule(istream &i) {
    if (i) {
        Schedule();
        this->read(i);
    } else {
        i.setstate(std::ios_base::failbit);
        throw runtime_error("istream fail");
    }
    /// wwwwwhhhhyyyyyyyyy/
}

/*
Schedule(C string)
Read Events from the given filename. Throw a runtime_error, including the filename, if the file can’t be opened. All the requirements of .read() apply.
*/
Schedule::Schedule(const char *str) {  //// create and pass as reference.
    Schedule();
    string x = to_string(*str);
    ifstream stream(str);
    if (stream.is_open()) {
        this->read(stream);
    } else {
        stream.setstate(std::ios_base::failbit);  /// set fail bit
        throw runtime_error(str);
    }
}

/*
Schedule(C++ string)
Read Events from the given filename. Throw a runtime_error, including the filename, if the file can’t be opened. All the requirements of .read() apply.
*/
Schedule::Schedule(std::string str) {
    Schedule();
    ifstream stream(str);
    if (stream.is_open()) {
        this->read(stream);
    } else {
        stream.setstate(std::ios_base::failbit);
        throw runtime_error(str);
    }
}

// destructor

/*
Copy constructor
Takes another object of the same class, and deep-copies the information, replacing any previous information.
*/
Schedule::Schedule(Schedule &rhs) {
    for (Event e : event_set) {
        rhs.event_set.insert(e);
    }
}

/*
Assignment operator
Takes another object of the same class, and deep-copies the information, replacing any previous information.
*/
Schedule &Schedule::operator=(const Schedule &o) {
    event_set.clear();
    for (Event e : o.event_set) {
        event_set.insert(e);
    }
    return *this;
}

/*
[size_t]
Given a zero-based index, return the corresponding Event by constant reference.
If the index is out of range, throw a range_error (not a runtime_error), including
the erroneous index and the number of Events in this Schedule.
For a Schedule s, a zero index must return the Event with the earliest date,
s[s.size()-1] must return the Event with the last date, and the Events in between
must be in nondescending order. It is not guaranteed that the subscript operator
will be called in any particular order.
Just an overloaded bracket operator
*/
const Event &Schedule::operator[](const size_t &t) const{
    // vector<Event> event_vector = {};  //(event_set.size());

    size_t counter = 0;
    for (auto &e : event_set) {
        if (counter == t) {
            return e;
        }
        counter++;
    }

    // int index = t;
    throw range_error("out of bounds");
    // return event_vector[index];
}

/*
Destructor
Destroys this object, including all the Events associated with it.
*/
Schedule::~Schedule() {
}

/*
.read(istream)
Read all Events from the istream, separated by whitespace, into the Schedule. This method does not replace previous contents—it adds to them.
Upon syntactic or semantic error:
set the istream to a failed state
the Schedule must contain all the previously-encountered Events in the istream up to the point or the error, and no Events from after that
the Schedule must not contain a half-constructed Event.
optionally: throw a runtime_error describing the problem
*/
void Schedule::read(istream &s) {
    string event_string;
    string event_string2;

    while (s >> event_string) {
        try {
            event_set.insert(Event(event_string));
        } catch (const runtime_error &f) {
            s.setstate(std::ios_base::failbit);
        }
    }
}

/*
.clear()
Make this Schedule empty. If it’s already empty, then make it quite empty.
*/
void Schedule::clear() {
    event_set.clear();
}

/*
.size()
Return the number of Events in this object, as a size_t.
*/
size_t Schedule::size() const {
    return event_set.size();
}

/*
.empty()
Return true iff this object has no Events.
*/
bool Schedule::empty() {
    return event_set.empty();
}

multiset<Event> Schedule::getSet() {
    return event_set;
}

/*
ostream << Schedule
Write all the Events in this Schedule to the ostream in YYYY-MM-DD format,
each followed by a newline. Write exactly eleven characters per Event–nothing else.
They must be written in chronological order, oldest events first, as described in
the [] operator.
*/
ostream &operator<<(std::ostream &os, Schedule &s) {
    for (Event e : s.getSet()) {
        os << e << '\n';
    }
    return os;
}


bool operator==(const Schedule& s1, const Schedule& s2) {
    // Compare sizes first
    if (s1.size() != s2.size()) {
        return false;
    }

    // Compare each event in the schedules
    auto it1 = s1.begin();
    auto it2 = s2.begin();
    while (it1 != s1.end() && it2 != s2.end()) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }

    return true;
}

Schedule::iterator Schedule::begin() const {
    return iterator(event_set.begin());
}

Schedule::iterator Schedule::end() const {
    return iterator(event_set.end()++);
}