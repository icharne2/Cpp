#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct List_1 {
	int liczba;
	string nazwa;
	string tytul;
	int rok;
	string autor;
	List_1* nastepny;	
};

//prototypy funkcji
void printList(List_1* poczatek);   //Wypisuje liste
void addToBack(List_1*& poczatek, int value, string naz, string tyt, int year, string a);   //Dodaje element na koniec listy
List_1* policzWystapienia(List_1* lista); //Zad 1.
List_1* findYear(List_1*& poczatek, int value); //Zad 2.
void czyAutor(List_1* poczatek, int value);	//Zad 3.
void removeFromFront(List_1*& poczatek); //Usuwanie listy

int main() {
	List_1* head = nullptr; 

	//Odczyt z pliku:
	ifstream odczyt("dane.txt");
	string linia;
	//Zmienne pomocnicze do tworzenia listy:
	int num, rok;
	string naz, tyt, a, r, num2;

	if (!odczyt.is_open()) {
		cout << "Wystapil problem z otwarciem pliku" << endl;
		return 1;
	}

	while (!odczyt.eof()) {
		getline(odczyt, linia);
		num2 = linia.substr(0, linia.find(','));
		linia.erase(0, linia.find(',')+2);
		naz = linia.substr(0, linia.find(','));
		linia.erase(0, linia.find(',') + 2);
		tyt = linia.substr(0, linia.find(','));
		linia.erase(0, linia.find(',') + 2);
		r = linia.substr(0, linia.find(','));
		linia.erase(0, linia.find(',') + 2);
		a = linia;
		num = stoi(num2);
		rok = stoi(r);
		addToBack(head, num, naz, tyt, rok,a);
	}

	//wypisanie listy
	//printList(head);

	cout << "\nZadanie 1." << endl;
	//Napisz funkcjê która wygeneruje listê wszyskich wykonawców obencych na licie wiêcej ni¿ raz. 

	List_1* wynik = policzWystapienia(head);

	cout << "Lista wszystkich wykonawcow:" << endl;
	while (wynik) {
		cout << wynik->nazwa << endl;
		wynik = wynik->nastepny;
	}

	cout << "\nZadanie 2." << endl;
	//Napisz funkcjê która zwróci listê utworów wydancyh w podanym roku
	int year;
	cout << "Podaj rok." << endl;
	cin >> year;

	cout << "Utwory w podanym roku:" << endl;
	List_1* wynik2 = findYear(head, year);
	printList(wynik2);

	cout << "\nZadanie 3." << endl;
	//Dla podanej pozycji na licie sprawd czy wykonacwa jest równie¿ autorem utworu (mo¿esz ale nie musisz skorzystaæ z w³asnej wiedzy)
	int poz;
	cout << "Podaj pozycje na liscie" << endl;
	cin >> poz;

	czyAutor(head, poz);

	//Czyszczenie pamiêci - usuwanie listy:
	removeFromFront(head);
	//printList(head);

	odczyt.close();
	system("pause");
	return 0;
}

void printList(List_1* poczatek) {
	if (!poczatek)
		cout << "Lista jest pusta.";
	while (poczatek) {
		cout << "Nazwa zespolu:" << poczatek->nazwa << endl;
		cout << "Tutyl:" << poczatek->tytul << endl;
		cout << "Rok wydania:" << poczatek->rok << endl;
		cout << "Autor/autorzy: " << poczatek->autor << endl;
		poczatek = poczatek->nastepny;
	}
	cout << endl;
}


void addToBack(List_1*& poczatek, int value, string naz, string tyt, int year, string a){
	//Je¿eli lista jest pusta
	if (!poczatek) {
		poczatek = new List_1{ value, naz, tyt, year, a, nullptr };
		return;	//Konczymy funkcje
	}	//W przeciwnym wypadku dodajemy nowy element za ostatnim na liscie

	List_1* koniec = poczatek;
	//Przejscie na koniec listy
	while (koniec->nastepny != nullptr) {
		koniec = koniec->nastepny;
	}
	//Dodanie elementu
	koniec->nastepny = new List_1{ value, naz, tyt, year, a, nullptr };
}

List_1* policzWystapienia(List_1* lista)
{
	List_1* wynik = NULL;

	while (lista) // dopóki nie dojdziemy do koñca listy
	{
		List_1* aktualny = wynik;
		// sprawdzamy, czy juz jest
		while (aktualny && aktualny->nazwa != lista->nazwa)
		{
			aktualny = aktualny->nastepny;
		}
		if (!aktualny) // jeli nie istnieje
		{
			aktualny = new List_1;
			aktualny->nazwa = lista->nazwa;
			aktualny->nastepny = wynik;
			wynik = aktualny;
		}
		lista = lista->nastepny;
	}
	return wynik;
}


List_1* findYear(List_1*& poczatek, int value) {
	List_1* wynik = nullptr;
	List_1* tmp = poczatek;

	while (tmp != nullptr) {
		if ((tmp->rok <= value) && (value <= tmp->rok)) {
			List_1* nowy = new List_1;
			nowy->liczba = tmp->liczba;
			nowy->nazwa = tmp->nazwa;
			nowy->rok = tmp->rok;
			nowy->tytul = tmp->tytul;
			nowy->autor = tmp->autor;

			nowy->nastepny = wynik;
			wynik = nowy;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}

void czyAutor(List_1* poczatek, int value) {
	string wykon;
	string aut;

	while (poczatek) {
		if (poczatek->liczba == value) {
			wykon = poczatek->nazwa;
			aut = poczatek->autor;
			if (aut.compare(wykon)) {
				cout << "Dla podanego numeru wykonawca jest autor" << endl;
			}
			else {
				cout << "Dla podanego numeru wykonawca NIE jest autor" << endl;
			}
		}
		poczatek = poczatek->nastepny;
	}
}

void removeFromFront(List_1*& poczatek) {
	if (!poczatek) {
		cout << "Lista jest pusta, nie ma nic do usuniecia" << endl;
	}
	else {
		while (poczatek) {
			List_1* tmp = poczatek;
			poczatek = poczatek->nastepny;
			delete tmp;
		}
	}
}
