#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bilet
{
private:
	 int CIBilet;
	 const int minNo;
	 const int maxNo;

public:
	Bilet() : minNo(0), maxNo(0){
		this->CIBilet = 0;
	}

	Bilet(int CIBilet, int mini, int maxi) : minNo(mini), maxNo(maxi){
		this->CIBilet = CIBilet;
	}

	Bilet(int mini, int maxi) : minNo(mini), maxNo(maxi) { 
		CIBilet = minNo;
	}

	void random() {
		CIBilet = (rand() % maxNo) + minNo;
	}

	string convertCI_tostring() {
		string s = to_string(CIBilet);
		return s;
	}

	int check_duplicate(int CIBilet) {
		if (this->CIBilet == CIBilet)
			return 0;
		else return 1;
	}

	void set_CIBilet(const int CIBilet){
		if (CIBilet >= 100000 && CIBilet <= 999999)
			this->CIBilet = CIBilet;
	}

	int get_CIBilet() {
		return CIBilet;
	}
	
	friend ostream& operator<<(ostream& f, Bilet& bil);

	friend istream& operator>>(istream& f, Bilet& bil);

	Bilet operator++(int i) {
		CIBilet++;
		return *this;
	}

	Bilet operator--(int i) {
		CIBilet--;
		return *this;
	}

	bool operator!() {
		return CIBilet <= maxNo && CIBilet >= minNo;
	}
};

