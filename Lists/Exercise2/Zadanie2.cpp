#include<iostream>
#include<fstream>
#include<string>
#include <vector>

using namespace std;

struct List_1 {
	string imie_nazwisko;
	int rok;
	string kraj;
	List_1* nastepny;	//WskaŸnik na nastepny element
	int osoby = 1;
};

void printList(List_1* poczatek);   //Wypisuje liste
void addToBack(List_1*& poczatek, string in, int y, string k);   //Dodaje element na koniec listy
List_1* findCountry(List_1* &poczatek, string value);
List_1* findYear(List_1*& poczatek, int value);
List_1* policzWystapienia(List_1* lista);

int main() {
	List_1* head = nullptr; //wskaŸnik na pierwszy element listy
	//Lista 2
	//Odczyt z pliku
	ifstream odczyt("nobel.txt");
	string linia;

	//Zmienne potrzebne do listy
	string i_n, k, r;
	int rok;

	//Sprawdzenie otwarcia pliku
	if (!odczyt.is_open()) {
		cout << "Wystapil problem z otwarciem pliku" << endl;
		return 1;
	}

	//Dopoki nie osiagniemy ostatniej lini
	while (!odczyt.eof()) {
		getline(odczyt, linia);
		i_n = linia.substr(0, linia.find('1') - 1);
		linia.erase(0, linia.find('1'));	//usuniecie imion
		r = linia.substr(0, 4); //data
		linia.erase(0, 5);	//usuwa date
		rok = stoi(r);
		k = linia;
		addToBack(head, i_n, rok, k);
	}

	//Napisz funkcjê, która by zwórci³a wszyskich laureatów pochodz¹cych z danego kraju
	string kraj;
	List_1* wynik1 = nullptr;

	cout << "Podaj kraj - z duzej litery" << endl;
	cin >> kraj;

	wynik1 = findCountry(head, kraj);

	printList(wynik1);

	//Napisz funkcjê, która by zwróci³a liste krajów z przypisanymi do nich iloœciami laureatów
	cout << "Liczba wystapien imion osob dla poszczegolnych krajow:\n";
	List_1* aktualny = policzWystapienia(head);

	while (aktualny != NULL)
	{
		cout << aktualny->kraj << ": " << aktualny->osoby << endl;
		aktualny = aktualny->nastepny;
	}


	//Napisz funkcjê, która by zwróci³a nazwisko laureata w podanym roku
	int year;
	List_1* wynik2 = nullptr;

	cout << "Podaj rok." << endl;
	cin >> year;

	wynik2 = findYear(head, year);	//Funkcja zwraca liste obiektow z podanego roku

	//Wypisywanie nazwisk
	while (wynik2) {
		string nazwisko;
		nazwisko = wynik2->imie_nazwisko.substr(wynik2->imie_nazwisko.rfind(' '), wynik2->imie_nazwisko.size()-(wynik2->imie_nazwisko.rfind(' ')));
		cout << "Nazwisko laureata:" << nazwisko << endl;
		wynik2 = wynik2->nastepny;
	}

	system("pause");
	return 0;
}

void printList(List_1* poczatek) {
	if (!poczatek)
		cout << "Lista jest pusta.";
	while (poczatek) {
		cout << "Imie i nazwisko: " << poczatek->imie_nazwisko << endl;
		cout << "Rok: " << poczatek->rok << endl;
		cout << "Kraj: " << poczatek->kraj << endl;
		poczatek = poczatek->nastepny;
	}
	cout << endl;
}

void addToBack(List_1*& poczatek, string in, int rok, string k) {
	//Je¿eli lista jest pusta
	if (!poczatek) {
		poczatek = new List_1{ in, rok, k, nullptr };
		return;	//Konczymy funkcje
	}	//W przeciwnym wypadku dodajemy nowy element za ostatnim na liscie

	List_1* koniec = poczatek;
	//Przejscie na koniec listy
	while (koniec->nastepny != nullptr) {
		koniec = koniec->nastepny;
	}
	//Dodanie elementu
	koniec->nastepny = new List_1{ in, rok, k, nullptr };
}

List_1* findCountry(List_1*& poczatek, string value) {
	List_1* wynik = nullptr;
	List_1* tmp = poczatek;

	while (tmp != nullptr) {
		if (tmp->kraj == value) {
			List_1* nowy = new List_1;
			nowy->imie_nazwisko = tmp->imie_nazwisko;
			nowy->kraj = tmp->kraj;
			nowy->rok = tmp->rok;

			nowy->nastepny = wynik;
			wynik = nowy;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}

List_1* findYear(List_1*& poczatek, int value) {
	List_1* wynik = nullptr;
	List_1* tmp = poczatek;

	while (tmp != nullptr) {
		if (tmp->rok == value) {
			List_1* nowy = new List_1;
			nowy->imie_nazwisko = tmp->imie_nazwisko;
			nowy->rok = tmp->rok;
			nowy->kraj = tmp->kraj;

			nowy->nastepny = wynik;
			wynik = nowy;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}

List_1* policzWystapienia(List_1* lista)
{
	List_1* wynik = NULL; 

	while (lista) // dopóki nie dojdziemy do koñca listy
	{
		List_1* aktualny = wynik;
		// sprawdzamy, czy nazwa kraju wystêpuje ju¿ na liœcie wynikowej
		while (aktualny && aktualny->kraj != lista->kraj)
		{
			aktualny = aktualny->nastepny;
		}
		if (!aktualny) // jeœli nazwa kraju nie wyst¹pi³a wczeœniej, dodajemy j¹ na listê
		{
			aktualny = new List_1;
			aktualny->kraj = lista->kraj;
			aktualny->nastepny = wynik;
			wynik = aktualny;
		}else // jeœli nazwa kraju ju¿ wyst¹pi³a wczeœniej, zwiêkszamy liczbê wyst¹pieñ
		{
			aktualny->osoby += 1;
		}
		lista = lista->nastepny; 
	}
	return wynik; 
}

