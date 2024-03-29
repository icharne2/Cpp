#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//Struktura listy jednokierunkowej - wzor struktury i funkcji odpowiednie do zadania
struct List_1 {
	string imie_nazwisko;
	int lata_poczatek;
	int lata_koniec;
	string partia;
	List_1* nastepny;	//Wskaünik na nastepny element
};

//prototypy funkcji
void printList(List_1* poczatek);   //Wypisuje liste
void addToFront(List_1*& poczatek, string in, int la_p, int la_k, string p);  //Dodaje element na poczatek listy
void addToBack(List_1*& poczatek, string in, int la_p, int la_k, string p);   //Dodaje element na koniec listy
void removeFromFront(List_1*& poczatek);    //Usuwa element z poczatku listy
void removeFromBack(List_1*& poczatek);     //Usuwa element z konca listy
List_1* find(List_1*& poczatek, string value);	//Funkcja wyszukujaca partie
List_1* findYear(List_1*& poczatek, int value); //Funcka szukajaca czy int value jest w przedziale lat
List_1* presidents(List_1*& poczatek);	//Funkcja zwracajaca liste prezydentow o najktorszym czasie rzadzenia

int main() {
	List_1* head = nullptr; //wskaünik na pierwszy element listy
	//Lista 1
	//Odczyt z pliku
	ifstream odczyt("presidents.txt");
	string linia;

	//Zmienne potrzebne do listy
	string i_n, lata, p;
	int r_p, r_k;

	//Sprawdzenie otwarcia pliku
	if (!odczyt.is_open()) {
		cout << "Wystapil problem z otwarciem pliku" << endl;
		return 1;
	}

	//Dopoki nie osiagniemy ostatniej lini
	while (!odczyt.eof()) {
		getline(odczyt, linia);
		i_n = linia.substr(0, linia.find('-') - 5);
		lata = linia.substr(linia.find('-') - 4, 9);	//Wyciecie calej daty
		//Zmiana na int
		r_p = stoi(lata.substr(0, 4));
		r_k = stoi(lata.substr(5, 9));
		p = linia.substr(linia.find('-') + 6, linia.size() - (linia.find('-') + 5));

		addToBack(head, i_n, r_p, r_k, p);
	}

	//najkrotszy czas rzadzenia
	List_1* w = presidents(head);

	printList(w);

	//Szukanie parti
	string szukana_partia;

	cout << "Podaj partie" << endl;
	cin >> szukana_partia;

	List_1* wynik = find(head, szukana_partia);

	cout << "Lista prezydentow nalezacych do tej partii:" << endl;
	printList(wynik);

	//Imie i nazwisko prezydenta ktory rzadzil w podanym roku
	int rok;
	cout << "Podaj rok." << endl;
	cin >> rok;

	cout << "Prezydent ktory rzadzil w podanym roku:" << endl;
	List_1* wynik2 = findYear(head, rok);
	printList(wynik2);

	odczyt.close();
	system("pause");
	return 0;
}

void printList(List_1* poczatek) {
	if (!poczatek)
		cout << "Lista jest pusta.";
	while (poczatek) {
		cout << "Imie i nazwisko: " << poczatek->imie_nazwisko << endl;
		cout << "Lata kandydatury: " << poczatek->lata_poczatek  << "-" << poczatek->lata_koniec << endl;
		cout << "Partia: " << poczatek->partia << endl;
		poczatek = poczatek->nastepny;
	}
	cout << endl;
}

List_1* find(List_1*& head, string szukanaPartia) {
	List_1* wynik = nullptr;
	List_1* tmp = head;

	while (tmp != nullptr) {
		if (tmp->partia == szukanaPartia) {
			List_1* nowy = new List_1;
			nowy->imie_nazwisko = tmp->imie_nazwisko;
			nowy->partia = tmp->partia;
			nowy->lata_poczatek = tmp->lata_poczatek;
			nowy->lata_koniec = tmp->lata_koniec;

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
		if ((tmp->lata_poczatek <= value) && (value <= tmp->lata_koniec)) {
			List_1* nowy = new List_1;
			nowy->imie_nazwisko = tmp->imie_nazwisko;
			nowy->partia = tmp->partia;
			nowy->lata_poczatek = tmp->lata_poczatek;
			nowy->lata_koniec = tmp->lata_koniec;

			nowy->nastepny = wynik;
			wynik = nowy;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}

List_1* presidents(List_1*& poczatek) {
	List_1* wynik = nullptr;
	List_1* tmp = poczatek;
	int czas = 1000;

	//Szukanie minimalnej kadencji
	while (tmp != nullptr) {
		if (czas > (tmp->lata_koniec - tmp->lata_poczatek)) {
			czas = (tmp->lata_koniec - tmp->lata_poczatek);
		}
		tmp = tmp->nastepny;
	}
	tmp = poczatek;

	//Sprawdzanie kto ma te czas rzadzenia
	while (tmp != nullptr) {
		if ((tmp->lata_koniec - tmp->lata_poczatek) == czas) {
			List_1* nowy = new List_1;
			nowy->imie_nazwisko = tmp->imie_nazwisko;
			nowy->partia = tmp->partia;
			nowy->lata_poczatek = tmp->lata_poczatek;
			nowy->lata_koniec = tmp->lata_koniec;

			nowy->nastepny = wynik;
			wynik = nowy;
		}
		tmp = tmp->nastepny;
	}
	return wynik;
}

void addToFront(List_1* &poczatek, string in, int la_p, int la_k, string p) {
	//Tworzenie nowego obiektu
	List_1* nowy = new List_1{ in, la_p, la_k, p, poczatek };
	poczatek = nowy;
}

void addToBack(List_1* & poczatek, string in, int la_p, int la_k, string p) {
	//Jeøeli lista jest pusta
	if (!poczatek) {
		poczatek = new List_1{ in, la_p, la_k, p, nullptr };
		return;	//Konczymy funkcje
	}	//W przeciwnym wypadku dodajemy nowy element za ostatnim na liscie

	List_1* koniec = poczatek;
	//Przejscie na koniec listy
	while (koniec->nastepny != nullptr) {
		koniec = koniec->nastepny;
	}
	//Dodanie elementu
	koniec->nastepny = new List_1{ in, la_p, la_k, p, nullptr };
}

void removeFromFront(List_1*& poczatek) {
	if (!poczatek) {
		cout << "Lista jest pusta, nie ma nic do usuniecia" << endl;
	}
	else {
		List_1* tmp = poczatek;
		poczatek = poczatek->nastepny;
		delete tmp;
	}
}

void removeFromBack(List_1*& poczatek) {
	if (!poczatek) {
		cout << "Lista jest pusta, nie ma nic do usuniecia" << endl;
	}
	//Jezeli mamy tylko jeden element
	if (!poczatek->nastepny) {
		delete poczatek;
		poczatek = nullptr;
	}//Gdy elementow jest powyzej 1
	else {
		List_1* tmp = poczatek;
		//Do przedostatniego elementu
		while (tmp->nastepny->nastepny) {
			tmp = tmp->nastepny;
		}
		delete tmp->nastepny;
		tmp->nastepny = nullptr;
	}
}