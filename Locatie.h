#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

using namespace std;

class Locatie
{
private:
	int nrLocuri;
	int nrRanduri;
	char* zona;
	int* nrScaun;
	
	static int count;
	int index = 1;

public:
	Locatie() {
		nrLocuri = nrRanduri = 0;
		zona = NULL;
		nrScaun = NULL;
		index = 0;
		count++;
	}

	Locatie(int nrLocuri, int nrRanduri, char* zona, int* nrScaun, int index) {
		this->nrLocuri = nrLocuri;
		this->nrRanduri = nrRanduri;
		this->zona = new char[strlen(zona) + 1];
		for (int i = 0; i < strlen(zona); i++)
			this->zona[i] = zona[i];
		this->zona[strlen(zona)] = '\0';
		this->nrScaun = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++)
			this->nrScaun[i] = nrScaun[i];
		this->index = index;
		count++;
	}

	int provideChairNo() {
		if (index <= nrLocuri) {
			index++;
			return nrScaun[index - 2];
		}
		else return -1;
	}

	void generate_nrScaun() {
		if (nrLocuri > 0){
			nrScaun = new int[nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				nrScaun[i] = i + 1;
		}
	}

	string get_zona_as_string() {
		string s{ zona };
		return s;
	}

	void set_nrLocuri(int nrLocuri) {
		if (nrLocuri > 0 && nrLocuri != this->nrLocuri) {
			this->nrLocuri = nrLocuri;
		}
	}

	void set_nrRanduri(int nrRanduri) {
		if (nrRanduri > 0)
			this->nrRanduri = nrRanduri;
	}

	void set_zona(char* zona) {
		if (zona != NULL) {
			this->zona = new char[strlen(zona) + 1];
			for (int i = 0; i < strlen(zona); i++)
				this->zona[i] = zona[i];
			this->zona[strlen(zona)] = '\0';
		}
	}

	void set_nrScaun(int* nrScaun, int nrLocuri) {
		this->nrScaun = new int[nrLocuri];
		this->nrScaun = nrScaun;
		for (int i = 0; i < nrLocuri; i++)
			this->nrScaun[i] = nrScaun[i];
	}
	
	void set_index(int index) {
		if (index)
			this->index = index;
	}

	void set_cout(int count) {
		if (count)
			count = count;
	}

	int get_nrLocuri() {
		return nrLocuri;
	}

	int get_nrRanduri() {
		return nrRanduri;
	}

	char* get_zona() {
		return zona;
	}

	int* get_nrScaun() {
		return nrScaun;
	}

	int get_index() {
		return index;
	}

	static int get_count() {
		return count;
	}

	friend ostream& operator<<(ostream& f, Locatie& loc);

	friend istream& operator>>(istream& f, Locatie& loc);

	Locatie operator=(Locatie loc) {
		this->nrLocuri = loc.nrLocuri;
		this->nrRanduri = loc.nrRanduri;
		this->zona = new char[strlen(loc.zona) + 1];
		for (int i = 0; i < strlen(loc.zona); i++)
			this->zona[i] = loc.zona[i];
		this->zona[strlen(loc.zona)] = '\0';
		this->nrScaun = new int[loc.nrLocuri];
		for (int i = 0; i < loc.nrLocuri; i++)
			this->nrScaun[i] = loc.nrScaun[i];
		this->index = loc.index;
		return *this;
	}

	int operator[](int i) {
		if (i < nrLocuri && i >= 0)
			return nrScaun[i];
		else return -1;
	}

	~Locatie() {
		free(zona);
		free(nrScaun);
	}
}; 