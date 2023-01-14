#pragma once
#include "Eveniment.h"
#include <cstring>
using namespace std;

class Eveniment_extended : public Eveniment
{
public:
	int checkDate(string date1, string date2) {
		if (strcmp(date1.c_str(), date2.c_str()) < 0) {
			return 1;
		}
		else if (strcmp(date1.c_str(), date2.c_str()) > 0) {
			return -1;
		}
		else {
			return 0;
		}
		return 0;
	}

	int checkHour(string ora1, string ora2) {
		if (strcmp(ora1.c_str(), ora2.c_str()) < 0) {
			return 1;
		}
		else if (strcmp(ora1.c_str(), ora2.c_str()) > 0) {
			return -1;
		}
		else {
			return 0;
		}
		return 0;
	}
};

