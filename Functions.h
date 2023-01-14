#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int validateDate(const std::string& date) {
    // verif. format data (dd/mm/yyyy)
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return 0;
    }
    // extragere dd, mm, yyyy
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) {
        return 0;
    }

    if (day < 1 || day > 31) {
        return 0;
    }

    if (month == 2) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            if (day > 29) {
                return 0;
            }
        }
        else {
            if (day > 28) {
                return 0;
            }
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return 0;
        }
    }

    if (year == 0) {
        return 0;
    }
    return 1;
}


int validateHour(const std::string& hour) {
    // verif. format hour (hh:mm)
    if (hour.size() != 5 || hour[2] != ':') {
        return 0;
    }
    // extragere hh, mm
    int hh = stoi(hour.substr(0, 2));
    int mm = stoi(hour.substr(3, 2));

    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
        return 0;
    }
    return 1;
}

