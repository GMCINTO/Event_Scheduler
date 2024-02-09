#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "validate.h"
#include <iostream>
#include <string>

class Event {
   public:
    Event(const char* str);

    Event(std::string str);  //take in const 

    Event(const Event& rhs); // copy constructor

    Event& operator=(const Event& o); // assignment operator

    Event() = delete; //restrict default constructor          /// come back to this!!!!!
    
    ~Event();  //destructor

    void set(int year, int month, int day);    // setter

    

    int year() const;      // year getter

    int month() const;       // month getter

    int day() const;      // day getter

    int date_index() const; // variable to help organize while placeing into map
    
        Event& operator++() {
        _day++;
        
        return *this;
    }

    // post-increment operator (Event++)
    Event operator++(int) {
        Event temp(*this);
        operator++();
        return temp;
    }

    // pre-decrement operator (--Event)
    Event& operator--() {
        _day--;
        
        return *this;
    }

    // post-decrement operator (Event--)
    Event operator--(int) {
        Event temp(*this);
        operator--();
        return temp;
    }

    std::string fmt() const;
    std::string fmt(std::string format) const;
    //std::string fmt(const std::string fmt) const;
    
   private:
    std::string inputString;
    int _year, _month, _day;
    int date_ind;

};


bool operator<(const Event &, const Event &);
bool operator>(const Event &, const Event &);
bool operator<=(const Event &, const Event &);
bool operator>=(const Event &, const Event &);
bool operator==(const Event& lhs, const Event& rhs);
bool operator!=(const Event& lhs, const Event& rhs);


std::ostream& operator<<(std::ostream &, Event &);


#endif /* EVENT_H_INCLUDED */
