#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Event.h"

class Schedule {
   public:
    Schedule();  // no arg

    Schedule(std::istream& s);  // istream arg

    Schedule(const char* str);  // char *

    Schedule(const std::string str);  // std::string

    Schedule(Schedule& rhs);  // copy constructor

    Schedule& operator=(const Schedule& o);  // assignment operator

    const Event& operator[](const size_t& t) const;

    ~Schedule();  // destructor

    void read(std::istream& s);

    void clear();

    size_t size() const;  // returns size of schedule list

    bool empty();  // returns true if empty

    std::multiset<Event> getSet();

    class iterator : public std::iterator<std::forward_iterator_tag, Event> {
       public:
        using value_type = Event;
        using reference = Event&;
        using pointer = Event*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator(std::multiset<Event>::iterator it) : sit(it) {}

        const Event& operator*() const {
            return *sit;
        }

        const Event* operator->() const {
            return &(*sit);
        }

        iterator& operator++() {
            ++sit;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --sit;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.sit == rhs.sit;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }

        // iterator begin();

        // iterator end();

       private:
        std::multiset<Event>::iterator sit;
    };

    iterator begin() const;

    iterator end() const;

   private:
    size_t sched_amt;
    std::multiset<Event> event_set;
};



std::ostream& operator<<(std::ostream& os, Schedule& s);

#endif /* SCHEDULE_H_INCLUDED */
