#pragma once
#include "Locatie.h"
#include <iostream>
#include <vector>
using namespace std;

class Locatie_extended : public Locatie
{
private: 
	vector<vector<int>> locuri;
	int nrTotal;
	int randuri;
	int coloane;
    int counter;

public:
	Locatie_extended() {
		int* Scaun = get_nrScaun();
		nrTotal = get_nrLocuri();
		randuri = get_nrRanduri();
        if(randuri > 0)
            coloane = nrTotal / randuri + 1;

        for (int i = 0; i < randuri; i++) {
            vector<int> row;
            for (int j = 0; j < coloane; j++) {
                if (i * coloane + j < nrTotal) {
                    row.push_back(Scaun[i * coloane + j]);
                }
                else {
                    row.push_back(-1);
                }
            }
            locuri.push_back(row);
        }

        for (int i = 0; i < locuri.size(); i++) {
            for (int j = 0; j < locuri[i].size(); j++) {
                cout << locuri[i][j] << " ";
            }
            cout << endl;
        }

        delete[] Scaun;
        counter = 0;
	}

    vector<vector<int>> get_locuri(){
        return locuri;
    }

    //metode virtuale
    void set_nrLocuri(int nr) {
        nrTotal = nr;
    }

    void set_nrRandrui(int nr) {
        randuri = nr;
    }

};

