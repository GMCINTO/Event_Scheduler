#include <cassert>
#include <iostream>
#include <sstream>

#include "Event.h"
#include "Schedule.h"
#include "Schedule.h"  // I meant to do that.

using namespace std;

int main() {
    istringstream tyt("tomorrow yesterday today");
    Schedule s(tyt);
    istringstream more("\t\r0100-10-10\f3000.365  ");
    s.read(more);
    // Should now contain:
    // 0: 0100-10-10
    // 1: yesterday
    // 2: today
    // 3: tomorrow
    // 4: 3000-12-31
        const auto s2(s);

        cout << s.size() << '\n' << s2.size() << '\n';
        assert(s.size() == s2.size());
        for (size_t i=0; i<s2.size(); i++)
            assert(s[i] == s2[i]);
        s.clear();
        assert(s.empty());
        assert(s.size() == 0);
        for (const Event &e : s2)
            cout << e.fmt() << e.fmt(" / %04Y.%j / %A %B %e %04Y%n");

        Schedule::iterator it = s2.begin();
        assert(*++it == s2[1]);
        assert(*it++ == s2[1]);
        assert(*it++ == s2[2]);
        assert(*it++ == s2[3]);
        assert(*it++ == s2[4]);
        assert(it == s2.end());
        assert(it-- == s2.end());
        assert(*it-- == s2[4]);
        assert(*--it == s2[2]);

        auto yesterday = *--it;
        auto today = *++it;
        auto tomorrow = *++it;

        assert(yesterday == s2[1]);
        assert(today == s2[2]);
        assert(tomorrow == s2[3]);

        const Event &first = s2[0];
        assert(first < today);
        assert(first <= today);
        assert(first != today);
        assert(today > first);
        assert(today >= first);

        return 0;
}