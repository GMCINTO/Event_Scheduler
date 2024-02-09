#include <stdio.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
string program_name;



void throw_err(string error_string) {
    //cout << "fail 1" << '\n';
    throw runtime_error("bad date: " + error_string);
    //setstate(std::ios_base::failbit);

}

void throw_err(int error_int){

    //cout << "fail 2" << '\n';
    throw runtime_error ("bad date: " + to_string(error_int));

}

/*
checks to see if any given year is leap year
takes in int - year to be checked
returns bool - true if given year is a leap year false if not
 */
bool is_lpyr(int year) {
    if (year % 400 == 0) {
        return true;
    } else if (year % 4 == 0 && year % 100 != 0) {
        return true;
    } else {
        return false;
    }
}

/*
creates time object *note: only used with YYYY.DDD input format
takes in two integers representing day(yday) and year
returns a time object representing the date of the given input
*/
tm create_tm(int day, int year) {
    tm tm{};  // zero initialise
    tm.tm_year = year - 1900;
    tm.tm_mday = day;
    tm.tm_hour = 12;
    tm.tm_isdst = -1;
    mktime(&tm);
    return tm;
}

/*
creates time object *note: only used with YYYY-MM-DD input format
takes in two integers representing day(yday) and year
returns a time object representing the date of the given input
*/
tm create_tm_2(int month, int day, int year) {
    tm tm{};  // zero initialise
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 12;
    tm.tm_isdst = -1;
    mktime(&tm);
    return tm;
}

/*
validates given date if date for legitimacy *note: only used with YYYY-MM-DD input format
takes in three integers representing year, day, month order
returns bool: true if date is valid, false if not.
*/
bool validator2(int inDateY, int inDateD, int inDateM) {
    bool lpyr = is_lpyr(inDateY);
    int max_years = 9999, max_months = 12;

    int month_max[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (lpyr) {
        month_max[1] = 29;
    }

    if ((inDateY < 0) || (inDateY > max_years)) {
        throw_err(inDateY);
        //cerr << program_name << " failed. Invalid input format: year: " << inDateY << '\n';              // here 
        //exit(1);
        return 1;
    }

    if ((inDateM < 0) || (inDateM > max_months)) {
        throw_err(inDateM);
        //cerr << program_name << " failed. Invalid input format: month: " << inDateM << '\n';             // here 
        //exit(1);
        return 1;
    }

    if ((inDateD < 0) || (inDateD > month_max[inDateM - 1])) {
        throw_err(inDateD);
        //cerr << program_name << " failed. Invalid input format: day: " << inDateD << '\n';               // here 
        //exit(1);
        return 1;
    }
    return true;
}

/*
validates given date if date for legitimacy *note: only used with YYYY.DDD input format
takes in two integers representing year, day(yday)
returns bool: true if date is valid, false if not.
*/
bool validator(int inDateY, int inDateD) {
    int maxDays = 365;
    int maxYears = 9999;
    bool lpyr = is_lpyr(inDateY);

    if (lpyr) {
        maxDays = 366;
    }

    if (inDateD > maxDays) {
        throw_err(inDateD);
        // cerr << program_name << " failed. Invalid input format: days: " << inDateD << '\n';          /// here 
        // exit(1);
        return 1;
    }

    if ((inDateY < 0) || (inDateY > maxYears)) {
        throw_err(inDateY);
        // cerr << program_name << " failed. Invalid input format: year: " << inDateY << '\n';           /// here 
        // exit(1);
        return 1;
    }
    return true;
}

/*
validates input string for any formating errors and parses into int values rep. date variables *note: only used if string contains '-'(YYYY-MM-DD)
takes in input string after fisrt round of input parsing at date_parser() function
checks all characters for validity
parses string into 3 integer values representing year month day 
sends these values to validator2() to be checked for valid input returns true or false. **fails in other function not here 
validated integers then are sent to create_tm_2() which returns tm object
returns time object returned by ctreate_tm_2()
*/
tm validateString2(string snd_date_fmt) { 
    int month = 0, day = 0, year = 0;
    string month_str = "", day_str = "", year_str = "";

    if (snd_date_fmt[4] != '-' || snd_date_fmt[7] != '-') {
        throw_err("invalid format: " + snd_date_fmt);
        // cerr << program_name << " failed. invalid input format.\n";                                              /// here
        // exit(1);
        //return 1;
    }

    ///// year
    for (int i = 0; i < 4; i++) {
        if (!isdigit(snd_date_fmt[i])) {
            throw_err("Invalid input format: "+ snd_date_fmt[i]);
            // cerr << program_name << " failed. Invalid input format: char: " << snd_date_fmt[i] << '\n';           /// here
            // exit(1);
        } else {
            year_str += snd_date_fmt[i];
        }
    }

    ///// month
    for (int j = 5; j < 7; j++) {
        if (!isdigit(snd_date_fmt[j])) {
            throw_err("Invalid input format: char: " + snd_date_fmt[j]);
            // cerr << program_name << " failed. Invalid input format: char: " << snd_date_fmt[j] << '\n';          /// here
            // exit(1);
        } else {
            month_str += snd_date_fmt[j];
        }
    }

    ///// Day
    for (int i = 8; i < 10; i++) {
        if (!isdigit(snd_date_fmt[i])) {
            throw_err("Invalid input format: char: " + snd_date_fmt[i]);
            // cerr << program_name << " failed. Invalid input format: char: " << snd_date_fmt[i] << '\n';           /// here
            // exit(1);
        } else {
            day_str += snd_date_fmt[i];
        }
    }

    //cout << "here2";
    month = stoi(month_str);
    day = stoi(day_str);
    year = stoi(year_str);

    if (validator2(year, day, month)) {
        return create_tm_2(month, day, year);
    } else {
        throw_err("validateString() error check fail.");
        // cerr << program_name << " failed. validateString() error check fail.";                             /// here
    }
    return create_tm_2(year, day, month); ////just to make compilier happy. shant be used 
}


/*
validates input string for any formating errors and parses into int values rep. date variables *note: only used if string contains '.'(YYYY.DDD)
takes in input string after fisrt round of input parsing at date_parser() function
checks all characters for validity
parses string into 3 integer values representing year day(yday) 
sends these values to validator() to be checked for valid input returns true or false. **fails in other function not here 
validated integers then are sent to create_tm() which returns tm object
returns time object returned by create_tm()
*/
tm validateString(string date) {
    int year = 0;
    int day = 0;

    string inDateYear;
    string inDateDay;
    string inDate = date;

    bool dSwitch = true;

    for (unsigned long int i = 0; i < inDate.size(); i++) {
        char x = inDate[i];

        if (x == '.') {
            dSwitch = false;
        }

        if (!isdigit(x) && x != '.') {
            throw_err(x);
            // cerr << program_name << " failed. Invalid input format: char: " << x << '\n';         //// here
            // exit(1);
        }

        if ((dSwitch) && x != '.') {
            inDateYear += x;
        } else if ((!dSwitch) && x != '.') {
            inDateDay += x;
        }
    }
    //cout << "here" << '\n';
    year = stoi(inDateYear);
    day = stoi(inDateDay);


    if (validator(year, day)) {
        return create_tm(day, year);
    } else {
        throw_err("validateString() error check fail.");
        //cerr << program_name << " failed. validateString() error check fail.";                     //// here
    }

    inDateYear = "";
    inDateDay = "";

    return create_tm(day, year);
}

/*
this checks to see if any two given strings match regardless of case
takes in two strings: each a word to be compared to the other
returns a bool. true if they match false if they dont
*/
bool string_matcher(string s1, string s2) {
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    if (s1.compare(s2) == 0) {
        return true;
    }
    return false;
}

/*
makes a time object representing yesterday
takes in nothing
returns time object representing yesterday
*/
tm create_tm_yesterday() {
    time_t current_time = time(NULL);
    time_t yesterday_time = current_time - 24 * 60 * 60;
    struct tm* yesterday = localtime(&yesterday_time);

    return *yesterday;
}

/*
makes a time object representing tomorrow
takes in nothing
returns time object representing tomorrow
*/
tm create_tm_tomorrow() {
    time_t current_time = time(NULL);
    time_t tomorrow_time = current_time + 24 * 60 * 60;
    struct tm* tomorrow = localtime(&tomorrow_time);

    return *tomorrow;
}

/*
makes a time object representing today
takes in nothing
returns time object representing today
*/
tm create_tm_today() {
    time_t current_time = time(NULL);
    tm* now = localtime(&current_time);

    return *now;
}

/*
checks a string to see if it contains a character
takes in a string that is to be checked and a character that is to be checked for
returns true if string contains the char and false if it doesnt
*/
bool fmt_chk(string ind, char seperator) {
    size_t found = ind.find(seperator);
    if (found != string::npos) {
        return true;
    } else {
        return false;
    }
}

/*
this seperated the string to be checked by respective functions depending on input format
if the string is one of the keyword strings its sent to the respective time creation functions
if the input string contains a period within its sent to validate_string
if the input string contains a dash within its sent to validate_string2
returns the time object created by a variety of different functions
*/
tm date_parser(string indate) {
    //cerr << indate << '\n';          ////remove
    string tday = "today";
    string tmor = "tomorrow";
    string yest = "yesterday";
    tm dummy{};

    if (string_matcher(tday, indate)) {
        return create_tm_today();
    } else if (string_matcher(tmor, indate)) {
        return create_tm_tomorrow();
    } else if (string_matcher(yest, indate)) {
        return create_tm_yesterday();
    } else if (fmt_chk(indate, '-')) {
        return validateString2(indate);
    } else if (fmt_chk(indate, '.')) {
        return validateString(indate);
    } else {
        throw_err("Invalid date input: " + indate);
        // cerr << program_name << " failed. Invalid date input: " << indate << '\n';
        // exit(1);
    }
    return dummy;
}
