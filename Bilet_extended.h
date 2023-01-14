#pragma once
#include "Bilet.h"
#include <iostream>
#include <random>

using namespace std;

class Bilet_extended : public Bilet
{
private: 
	int CIBilet;
	int minNo;
	int maxNo;

public: 
	Bilet_extended(int min, int max) {
		minNo = min;
		maxNo = max;
		CIBilet = -1;
	}

	int random() {
		// genarare securizata de cod bilet
		random_device rd;  // secure RNG
		mt19937 gen(rd());  // Mersenne Twister engine
		uniform_int_distribution<> dis(minNo, maxNo);  
		CIBilet = dis(gen);
		return CIBilet;
	}

	int check_duplicate(int CIBilet) {
		if (this->CIBilet == CIBilet) {
			random(); //reshuffle 
			return 0;
		}
		else return 1;
	}

};

