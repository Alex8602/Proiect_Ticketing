#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int validateDate(string date) {

    //Format data dd/mm/yyyy
    char chr[11]; //max 10+1 elem exista in formatul dorit al datei
    date.erase(std::remove_if(date.begin(), date.end(), ::isspace), date.end()); //sterge spatii albe
    date.resize(10); // resize la valoarea char 
    strcpy(chr, date.c_str());
    char delim[] = "/";
    int year=-1, month=-1, day=-1;

    char* token = strtok(chr, delim);
    while (token) {
        for (int i = 0; i < strlen(token); i++)
            if (isdigit(token[i]) == 0)
                return 0;
        if (day == -1)
            day = atoi(token);
        if (month == -1)
            month = atoi(token);
        year = atoi(token);

        token = strtok(NULL, delim);
    }

    if (1000 <= year <= 3000)
    {
        if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 0 && day <= 31)
            return 1;
        else
            if (month == 4 || month == 6 || month == 9 || month == 11 && day > 0 && day <= 30)
                return 1;
            else
                if (month == 2)
                {
                    if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day > 0 && day <= 29)
                        return 1;
                    else if (day > 0 && day <= 28)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
    }
    else
        return 0;
}

int validateHour(string hour) {
    char chr[6]; //max 5+1 elem exista in formatul dorit al datei
    hour.erase(std::remove_if(hour.begin(), hour.end(), ::isspace), hour.end()); 
    hour.resize(5);
    strcpy(chr, hour.c_str());
    char delim[] = ":";
    int hh = -1, mm = -1;

    char* token = strtok(chr, delim);
    while (token) {
        for (int i = 0; i < strlen(token); i++)
            if (!isdigit(token[i]))
                return 0;
        if (hh == -1)
            hh = atoi(token);
        mm = atoi(token);

        token = strtok(NULL, delim);
    }

    if (hh >= 0 && hh <= 24)
        if (mm >= 0 && mm <= 59)
            return 1;
        else return 0;
    else return 0;
}
