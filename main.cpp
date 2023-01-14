#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <conio.h>
#include "Locatie.h"
#include "Eveniment.h"
#include "Bilet.h"
#include "Functions.h"
#include "Locatie_extended.h"
#include "Bilet_extended.h"
#include "Eveniment_extended.h"
#include "Tokens.h"

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


//Running code


int main(int argc, char* argv[])
{

	char c;
	Tokens tk;
	//tk.reset();
	//tk.init();
	//tk.set_iter_to_first_unused_ticket();
	Bilet_extended bil(100000, 999999);
	vector <Locatie*> locatie;
	Eveniment ev;

	if (argc == 2) {
		string file_name = argv[1];
		ifstream file(file_name);

		string denumire, data, ora, zona;
		int nrMaxLoc, nrRanduri, nrBilete;
		char chr;

		if (file.fail()) {
			cerr << "Fisierul nu a putut fi incarcat! Abort!" << endl;
			return 1;
		}
		else {
			file >> denumire;
			if (denumire == "" || denumire == " ") cerr << "Denumirea evenimentului nu poate fi nula!" << endl;
			file >> data;
			if (!validateDate(data)) cerr << "Data evenimentului este invalida" << endl;
			file >> ora;
			if (!validateHour(ora)) cerr << "Ora evenimentului este invalida" << endl;

			ev.set_denumire(denumire);
			ev.set_data(data);
			ev.set_ora(ora);

			do {
				file >> zona;
				if (zona == "" || denumire == " ") cerr << "Denumirea locatiei nu poate fi nula" << endl;
				file >> nrMaxLoc;
				if (nrMaxLoc <= 0) cerr << "Nr de scaune nu poate fi <= decat 0" << endl;
				file >> nrRanduri;
				if (nrRanduri <= 0) cerr << "Nr de randuri nu poate fi <= decat 0" << endl;

				Locatie* loc = new Locatie();
				loc->set_nrLocuri(nrMaxLoc);
				loc->set_nrRanduri(nrRanduri);
				char* cstr = new char[zona.length() + 1];
				for (int i = 0; i < zona.length(); i++)
					cstr[i] = zona[i];
				cstr[zona.length()] = '\0';
				loc->set_zona(cstr);
				loc->generate_nrScaun();
				locatie.push_back(loc);


				int contor = 1;
				for (int i = 0; i < nrRanduri; i++) {
					for (int j = 0; j < nrMaxLoc / nrRanduri + 1; j++) {
						if (contor > nrMaxLoc) break;
						int ci;
						cout << "ok";
						do {
							ci = bil.random();
							if (tk.checkBilet(ci) == 0) break;
						} while (true);
						tk.push_ticket(denumire, data, ora, zona, i + 1, contor, ci);
						contor++;
					}
					if (contor >= nrMaxLoc)
						break;
				}

				file >> chr;
				chr = tolower(chr);
				if (chr == 'n') break;
			} while (true);
			file.close();
		}
	}


	int nrMaxLoc, nrRanduri, nrBilete;
	string data, ora, denumire, zona;


	start:
	system("CLS"); //clear screen command
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

			tk = Tokens();
			locatie.clear();
			ev.reset();
			tk.reset();


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


				int contor = 1;
				for (int i = 0; i < nrRanduri; i++) {
					for (int j = 0; j < nrMaxLoc / nrRanduri + 1; j++) {
						if (contor > nrMaxLoc) break;
						int ci;
						do {
							ci = bil.random();
							if (tk.checkBilet(ci) == 0) break;
						}while(true);
						tk.push_ticket(denumire, data, ora, zona, i+1, contor, ci);
						contor++;
					}
					if (contor >= nrMaxLoc)
						break;
				}

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

			cout << endl << endl << "Date introduse cu succes" << endl;
			cout << "-----------------------------------------------------------------" << endl << endl;
			do {
				char cc;
				cout << endl << "Apasa enter sau orice tasta pentru reintoarcere la meniu ";
				cc = _getch();
				if (cc)
					break;
			} while (true);
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

			string msg = tk.get_ticket();
			if (msg != "NULL")
				cout << msg;
			else cout << "Nu mai sunt bilete disponibile";
			do {
				char cc;
				cout << endl << endl << endl << "Apasa enter sau orice tasta pentru reintoarcere la meniu ";
				cc = _getch();
				if (cc)
					break;
			} while (true);
			goto start;
		}

		case '4': {
			cout << "Bun venit la eveniment!" << endl;
			cout << endl << "Va rugam validati biletul, introducand codul acestuia mai jos:" << endl << endl;
			bool oki = false;
			do {
				string cc;	
				int ci;
				cout << "Codul biletului: ";
				cin >> cc;
				try {
					ci = stoi(cc);
				}
				catch (invalid_argument) {
					ci = -1;
				}
				if (ci != -1 && ci >= 100000 && ci <= 999999)
					if (tk.checkBilet(ci) == 1) { oki = true; break; }
					else cout << endl << endl << "Biletul nu este valid" << endl << endl;
				else cout << endl << endl << "Acesta nu reprezinta un cod de bilet" << endl << endl;
				cout << "--------------------------------------------------" << endl;
				char ccc;
				cout << endl << endl << endl << "Apasa 'r' pentru reintoarcere la meniul principal, \n\tsau orice alta tasta pentru reincercrea introducerii codului"<<endl<<endl;
				ccc = _getch();
				ccc = tolower(ccc);
				if (ccc == 'r')
					goto start;
			} while (true);

			if (oki) {
				do {
					char cc;
					cout << endl << "Biletul este valid" << endl;
					cout << endl << endl << endl << "Apasa enter sau orice tasta pentru reintoarcere la meniu ";
					cc = _getch();
					if (cc)
						break;
				} while (true);
			}
			goto start;
		}

		case '5': {
			cout << endl << endl << "Multumim pentru utilizare!" << endl << endl <<endl;
			return 0;
		}

	}

	



}

