#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>
#include "Locatie.h"
#include "Eveniment.h"
#include "Bilet.h"
#include "Functions.h"

using namespace std;

// Definire overloading operatori >> si <<; initializare membru static

int Locatie::count = 0;

ostream& operator>>(ostream& f, Eveniment& ev) {
	f << ev.get_denumire();
	f << ev.get_data();
	f << ev.get_ora();
	return f;
}

istream& operator>>(istream& f, Eveniment& ev) {
	string denumire, data, ora;
	f >> denumire;
	f >> data;
	f >> ora;
	ev.set_data(data);
	ev.set_ora(ora);
	ev.set_denumire(denumire);
	return f;
}

ostream& operator<<(ostream& f, Locatie& loc) {
	f << loc.get_nrLocuri();
	f << loc.get_nrRanduri();
	f << loc.get_zona();
	int* nrScaun = loc.get_nrScaun();
	for (int i = 0; i < loc.get_nrLocuri(); i++)
		f << nrScaun[i];
	return f;
}

istream& operator>>(istream& f,  Locatie& loc) {
	int nrLocuri, nrRanduri;
	static int *nrScaun = NULL;
	int a;
	char* zona = NULL;
	f >> nrLocuri;
	f >> nrRanduri;
	f >> zona;
	nrScaun = new int[nrLocuri];
	for (int i = 0; i < nrLocuri; i++) {
		f >> a;
		nrScaun[i] = a;
	}
	loc.set_nrLocuri(nrLocuri);
	loc.set_nrRanduri(nrRanduri);
	loc.set_zona(zona);
	loc.set_nrScaun(nrScaun, nrLocuri);
	return f;
}

ostream& operator<<(ostream& f, Bilet& bil) {
	f << bil.get_CIBilet();
	return f;
}

istream& operator>>(istream& f, Bilet& bil) {
	int CIBilet;
	f >> CIBilet;
	bil.set_CIBilet(CIBilet);
	return f;
}


struct BileteVandute {
	string denumire, data, ora, zona;
	int rand, nrScaun, CIBilet;
};


//Running code


int main()
{
	int nrMaxLoc, nrRanduri, nrBilete;
	string data, ora, denumire, zona;

	char c;
	vector <Locatie*> locatie;
	vector <vector<int>> BileteZona;
	vector <string> Zone;
	vector <BileteVandute> Biletele;
	Eveniment ev;

	start:
	system("CLS");
	//Optiuni meniu
	cout << "================================================================" << endl;
	cout << "                        The ticketing app                       " << endl;
	cout << "----------------------------------------------------------------" << endl;

	do {
		cout << "(1) Introducere date " << endl;
		cout << "(2) Obtine informatii despre eveniment si locatie " << endl;
		cout << "(3) Cumpara un bilet " << endl;
		cout << "(4) Valideaza un bilet " << endl;
		cout << "(5) Iesire din aplicatie" << endl << endl;
		cout << "Introduceti numarul optiunii alese: ";
		c = _getche();
		cout << endl << endl;
		if (isdigit(c) && (c == '1' || c == '2' || c == '3' || c == '4' || c == '5'))
			break;
		else 
			cout << endl << "Optiunea introdusa nu este valida. Va rugam realegeti din optiunile urmatoare:"<<endl<<endl;
	} while (true);


	switch (c) {

		case '1': {
			cout << "Introduceti urmatoarele date referitoare la eveniment:" << endl;

			do {
				cout << "> Denumire: ";
				getline(cin, denumire);
				if (denumire != "" && denumire != " ")
					break;
				else
					cout << "Va rugam completati cu o denumire:" << endl << endl;
			} while (true);

			 cout << endl;

			do {
				cout << "> Data (format dd/mm/yyyy): ";
				cin >> data;
				if (validateDate(data))
					break;
				else
					cout << "Data introdusa nu este corecta. Reintroduceti:" << endl << endl;
			} while (true);
			cout << endl;

			do {
				cout << "> Ora (format hh:mm): "; 
				cin >> ora;
				if (validateHour(ora))
					break;
				else
					cout << "Ora introdusa nu este corecta. Reintroduceti:" << endl << endl;
			} while (true);
			cout << endl;

			ev.set_denumire(denumire);
			ev.set_data(data);
			ev.set_ora(ora); 

			cout << "----------------------------------------------------------------" << endl;
			char cc;
			do {

				Locatie *loc = new Locatie();

				cout << "Introduceti urmatoarele date referitoare la locatie:" << endl;
				cout << "> Nr. max de locuri: "; cin >> nrMaxLoc; cout << endl;
				cout << "> Nr de randuri: "; cin >> nrRanduri; cout << endl;
				cout << "> Denumirea zonei: "; cin >> zona; cout << endl;
				cout << "------------------------------------------------------------" << endl;

				loc->set_nrLocuri(nrMaxLoc);
				loc->set_nrRanduri(nrRanduri);
				char* cstr = new char[zona.length() + 1];
				for (int i = 0; i < zona.length(); i++)
					cstr[i] = zona[i];
				cstr[zona.length()] = '\0';
				loc->set_zona(cstr);
				loc->generate_nrScaun();
				locatie.push_back(loc);

				Zone.push_back(loc->get_zona_as_string());
				vector <int> aux;
				for (int i = 0; i < nrMaxLoc; i++) {
					reiterate:
					Bilet bil(100000, 999999);
					bil.random();
					int CI = bil.get_CIBilet();
					if (find(aux.begin(), aux.end(), CI) != aux.end())
						goto reiterate;
					else aux.push_back(CI);
				}

				BileteZona.push_back(aux);

				recheck:
				cout << "Doriti sa mai introduceti o locatie? (d/n): ";
				cc = _getche();
				cout << endl << endl;
				cc = tolower(cc);
				if (cc == 'n')
					break;
				if (cc != 'd') {
					cout << "Optiune invalida! Va rugam reselectati:" << endl << endl;
					goto recheck;
				}
			} while (true);

			cout << "Date introduse cu succes" << endl;
			cout << "-----------------------------------------------------------------" << endl << endl;
			goto start;
		}

		case '2': {
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Au fost intoduse urmatoarele date:" << endl << endl;
			cout << "Eveniment:" << endl;
			cout << "> Denumire: " << ev.get_denumire() << endl;
			cout << "> Data: " << ev.get_data() << endl;
			cout << "> Ora: " << ev.get_ora() << endl;

			cout << endl;
			if (1 == (int)locatie[0]->get_count())
				cout << "Locatie:" << endl << endl;
			else
				cout << "Locatiile: " << endl << endl;
			for (int i = 0; i < locatie.size(); i++) {
				locatie[i]->set_index(1);
				cout << "> Zona: " << locatie[i]->get_zona_as_string() << endl;
				cout << "> Nr. locuri: " << locatie[i]->get_nrLocuri() << endl;
				cout << "> Nr. randuri: " << locatie[i]->get_nrRanduri() << endl;
				
				cout << "Amplsarea scaunelor este urmatoarea:" << endl;
				for (int k = 0; k < locatie[i]->get_nrRanduri(); k++) {
					cout << "Randul " << k + 1 << ": ";
					for (int j = 1; j <= locatie[i]->get_nrLocuri() / locatie[i]->get_nrRanduri() + 1; j++) {
						int aux = locatie[i]->provideChairNo();
						if (aux < 10 && aux != -1)
							cout << " " << aux << " ";
						else if (aux > 9)
							cout << aux << " ";
						else if (aux == -1)
							cout << "   ";
					}
					cout << endl;
				}
				cout << endl;
				locatie[i]->set_index(1);
			}
			do {
				char cc;
				cout << endl << "Apasa enter sau orice tasta pentru reintoarcere la meniu ";
				cc = _getch();
				if (cc)
					break;
			} while (true);
			cout << endl << "----------------------------------------------------------------" << endl;
			goto start;
		}
			
		case '3': {
			cout << endl;
			cout << "Selectare bilete"<<endl;
			cout << "Selectati o zona: ";
			string zona;
			int nr;
			cin >> zona;
			int contor=0;
			for(int i=0;i<Zone.size();i++)
				if (Zone[i] == zona) {
					nr = i;
					break;
				}
			if (BileteZona[nr].size() > 0) {
				// ...
			}
			else cout << "Nu mai sunt locuri in zona " << Zone[nr] << ". Va rugam alegti o alta zona";

			goto start;
		}

		case '4': {
			cout << "...in constructie..." << endl;
			goto start;
		}

		case '5': {
			cout << endl << endl << "Multumim pentru utilizare!" << endl << endl;
			return 0;
		}

	}

	



}

