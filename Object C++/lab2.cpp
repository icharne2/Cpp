#include<iostream>
#include<string>
using namespace std;

class Pasazer {
private:
	string imie;
	string nazwisko;
	int wiek;
public:
	Pasazer() {};
	Pasazer(string name, string lastName, int year) : imie(name), nazwisko(lastName), wiek(year) {};

	//Aby miec dostep do danych

	void setName(string imie) {
		this->imie = imie;
	}

	void setLastName(string nazwisko) {
		this->nazwisko = nazwisko;
	}

	void setYear(int wiek) {
		this->wiek = wiek;
	}

	string getLastName() {
		return nazwisko;
	}

	void printInfo() {
		cout << "Imie: " << imie << "\nNazwisko: " << nazwisko << "\nWiek: " << wiek << endl;
	}

};

class Autokar {
private:
	string miejsce_docelowe;
	const int ilosc_miejsc = 15;
	int zajete = 0;
	Pasazer* pasazerowie[15];
public:
	void setDestination(string miejsce_docelowe) {
		this->miejsce_docelowe = miejsce_docelowe;
	}

	void wypisz() {
		cout << "Miejsce docelowe: " << miejsce_docelowe << "\nMaksymalna liczba miejsc w autokarze: " << ilosc_miejsc << endl;
		
		cout << "Lista pasazerow: " << endl;
		for (int i = 0; i < zajete; i++) {
			pasazerowie[i]->printInfo();
		}
	}

	void dodajPasazerow(Pasazer array[]) {
		if (zajete < ilosc_miejsc) {
			for (int i=0; zajete < ilosc_miejsc; zajete++, i++) {
				this->pasazerowie[zajete] = &array[i];
			}
			if (zajete == ilosc_miejsc) {
				cout << "Osiagnieto maksymalna liczbe osob w autokarze. " << endl;
			}
		}
		else {
			cout << "Autokar jest caly zapelniony :<." << endl;
		}
	}

	void zmienWiek() {
		int w, person;
		cout << "Podaj numer osoby, ktora chcesz zmienic.[1-15]" << endl;
		cin >> person;
		cout << "Podaj nowy wiek" << endl;
		cin >> w;

		this->pasazerowie[person-1]->setYear(w);

	}
};

int main() {
	/*
	Utwórz obiekt klasy Pasazer i przypisz mu dowolne dane przy użyciu akcesorów. Wypisz nazwisko
	pasażera przy użyciu akcesora
	*/
	Pasazer p1;

	//Ustawienie danych dla pasazera uzywajac akcesorow:
	p1.setName("Jan");
	p1.setLastName("Kowalski");
	p1.setYear(35);

	//Wypisanie nazwiska pasażera przy użyciu akcesora
	cout << "Nazwisko pasazera: " << p1.getLastName() << endl;

	/*
	Utwórz tablicę dynamiczną obiektów klasy Pasazer o ilości elementów równej 200 o dowolnych
	danych.
	*/
	Pasazer* array = new Pasazer[200];

	//Zapełnienie tablicy
	for (int i = 0; i < 200; i++) {
		Pasazer tmp;
		tmp.setName("Imie_" + to_string(i+1));
		tmp.setLastName("Nazwisko_" + to_string(i+1));
		tmp.setYear(i + 20);
		array[i] = tmp;
	}

	//wypisanie tablicy:
	/*for (int i = 0; i < 200; i++) {
		array[i].printInfo();
	}
	*/

	/*
	Utwórz obiekt klasy Autokar i przypisz mu miejsce docelowe, do którego się udaje. 
	Do autokaru dodaj utworzoną (w punkcie b) tablicę obiektów klasy Pasazer (przestrzegaj limitu ilości miejsc). Wyświetl
	dane autokaru wraz z listą pasażerów.
	*/
	Autokar autokar1;
	autokar1.setDestination("Cracow");
	autokar1.dodajPasazerow(array);
	autokar1.wypisz();

	//Sprawdzenie komunikatu o zapelnieniu
	autokar1.dodajPasazerow(array);
	
	/*
	Zmień wiek dowolnego pasażera z autokaru używając metody zmienWiek(). Wyświetl dane
	autokaru wraz z listą pasażerów
	*/
	autokar1.zmienWiek();

	system("PAUSE");
	return 0;
}
