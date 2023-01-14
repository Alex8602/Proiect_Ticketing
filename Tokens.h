#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include "Rezervari.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Ticket {
	string eveniment, data, ora, zona;
	int rand, loc, CIBilet;
	bool taken;
};

class Tokens : public Rezervari
{
private: 
	int iter;
	vector<Ticket> tickets;

public:
	Tokens() {
		iter = 0;
	}

	void push_ticket(string eveniment, string data, string ora, string zona, int rand, int loc, int CIBilet) {
		Ticket t{ eveniment, data, ora, zona, rand, loc, CIBilet, false };
		// append in fisier
		ofstream file("tickets.data", ios::binary | ios::app);
		if (file.fail())
			cerr << "Eroare la scrierea datelor" << endl;
		file.write(reinterpret_cast<char*>(&t), sizeof(Ticket));
		file.close();

		tickets.push_back(t);
	}

	string get_ticket() {
		if (iter < tickets.size()) {
			string eveniment = tickets[iter].eveniment;
			string data = tickets[iter].data;
			string ora = tickets[iter].ora;
			string zona = tickets[iter].zona;
			string rand = to_string(tickets[iter].rand);
			string loc = to_string(tickets[iter].loc);
			string CIBilet = to_string(tickets[iter].CIBilet);
			tickets[iter].taken = true;
			iter++;
			updateFile();
			return "Eveniment: " + eveniment + "\nData: " + data + "\nOra: " + ora + "\n\nZona: " + zona + "\nRandul: " + rand + "\nLocul: " + loc + "\n\nCod Bilet: " + CIBilet;
		}
		else return "NULL";
	}

	void reset_iter() {
		iter = 0;
	}

	int checkBilet(int ci) {
		auto it = find_if(tickets.begin(), tickets.end(), [&ci](const Ticket& t) {return t.CIBilet == ci; }); 
		if (it != tickets.end())
			return 1;
		else return 0;
	}

	void set_iter(int iter) {
		if (iter) {
			this->iter = iter;
		}
	}

	void set_iter_to_first_unused_ticket() {
		auto it = find_if(tickets.begin(), tickets.end(), [](const Ticket& t) { return !t.taken; });
		if (it != tickets.end()) {
			iter = distance(tickets.begin(), it);
		}
	}

	void reset() {
		iter = 0;
		tickets.clear();
		// trunc file
		ofstream file("tickets.data", ios::binary | ios::trunc);

		file.close();
	}

	void init() {
		iter = 0;

		ifstream file("tickets.data", ios::binary );
		if(file.fail())
			cout << "Eroare la importarea datelor" << endl;

		while (!file.eof()) {
			Ticket t;
			if (file.fail()) {
				cout << file.rdstate();
			}
			if (!file.read(reinterpret_cast<char*>(&t), sizeof(Ticket)).fail()) {
				tickets.push_back(t);
			}
			else {
				cout << "err";
				cerr << "err";
			}

			if (file.fail()) {
				cerr << "Eroare la reimportarea datelor" << endl;
				break;
			}
			
		}

		file.close();
	}

	void updateFile() {
		// Trunc file
		std::ofstream file1("tickets.data", ios::binary | ios::trunc);
		file1.close();

		ofstream file("tickets.data", ios::binary | ios::app);
		if (file.fail())
			cerr << "Eroare la actualizarea datelor" << endl;
		for (const auto& t : tickets) {
			file.write(reinterpret_cast<const char*>(&t), sizeof(Ticket));
		}
		file.close();
	}



	~Tokens() {
		fstream file("tickets.data");
		if(file.is_open())
			file.close();
	}
};

