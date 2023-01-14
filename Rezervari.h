#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Rezervari
{
public: 

	Rezervari() {
	}

	virtual void push_ticket(string eveniment, string data, string ora, string zona, int rand, int loc, int CIBilet) = 0;

	virtual string get_ticket() = 0;

};

