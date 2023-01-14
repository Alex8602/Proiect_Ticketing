#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;

class Eveniment
{
private:
	string denumire;
	string data;
	string ora;

public:
	Eveniment() {
		data = ora = denumire = "";
	}

	Eveniment(string denumire, string data, string ora) {
		this->data = data;
		this->ora = ora;
		this->denumire = denumire; 
	}

	virtual int checkDate(string data) {
		if (this->data < data)
			return -1;
		else if (this->data == data)
			return 0;
		else return 1;
	}

	virtual int checkHour(string ora) {
		if (this->ora < ora)
			return -1;
		else if (this->ora == ora)
			return 0;
		else return 1;
	}

	void set_data(string data) {
		if (data != "")
			this->data = data;
	}

	void set_ora(string ora) {
		if (ora != "")
			this->ora = ora;
	}

	void set_denumire(string denumire) {
		if (denumire != "")
			this->denumire = denumire;
	}

	string get_data() {
		return data;
	}

	string get_ora() {
		return ora;
	}

	string get_denumire() {
		return denumire;
	}

	friend ostream& operator>>(ostream& f, Eveniment& ev);

	friend istream& operator>>(istream& f, Eveniment& ev);

	explicit operator string() {
		string s = denumire + " " + data + " " + ora + " ";
		return s;
	}

	string operator>(Eveniment& ev) {
		char c1[10], c2[10];
		strcpy(c1, ora.c_str());
		strcpy(c2, ev.ora.c_str());
		if (strcmp(c1, c2) > 0)
			return ora;
		else return "dif";
	}

	string operator<(Eveniment& ev) {
		char c1[10], c2[10];
		strcpy(c1, ora.c_str());
		strcpy(c2, ev.ora.c_str());
		if (strcmp(c1, c2) < 0)
			return ev.ora;
		else return "dif";
	}

	string operator==(Eveniment& ev) {
		char c1[10], c2[10];
		strcpy(c1, ora.c_str());
		strcpy(c2, ev.ora.c_str());
		if (strcmp(c1, c2) ==0)
			return ev.ora;
		else return "dif";
	}

	void reset() {
		data = ora = denumire = "";
	}

};

