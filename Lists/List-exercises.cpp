#include<iostream>

using namespace std;

//Struktura listy jednokierunkowej
struct List_1 {
    int wartosc;
    List_1* nastepny;	//Wskaünik na nastepny element
};

//prototypy funkcji
void printList(List_1* poczatek);   //Wypisuje liste
void addToFront(List_1*& poczatek, int value);  //Dodaje element na poczatek listy
void addAfter(List_1*& poczatek, int valueToInsertAfter, int value);    //Dodaje element na wskazany element
void addToBack(List_1*& poczatek, int value);   //Dodaje element na koniec listy
void removeFromFront(List_1*& poczatek);    //Usuwa element z poczatku listy
void removeFromBack(List_1*& poczatek);     //Usuwa element z konca listy
void removeAfter(List_1*& poczatek, int value);     //Usuwa element po wskazanym
void removeFind(List_1*& poczatek, int value);      //Usuwa pierwszy wskazany element
List_1* find(List_1*& poczatek, int value);	//Funkcja wyszukujaca dany element listy i zwracajaca go (szuka po wartosci)

int main() {
	List_1* head = nullptr; //wskaünik na pierwszy element listy
	

	system("pause");
	return 0;
}

void printList(List_1 * poczatek) {
	if (!poczatek)
		cout << "Lista jest pusta.";
	while (poczatek) {
		cout << poczatek->wartosc << " ";
		poczatek = poczatek->nastepny;
	}
	cout << endl;
;}

List_1* find(List_1 * &poczatek, int value) {
	List_1* current = poczatek;

	//Szukanie elementu 
	while (current && (current->wartosc != value)) {	//Kolejnosc warunku ma znaczenie
		current = current->nastepny;
	}
	return current;	//	Zwraca szukany element listy
}

void addToFront(List_1 * &poczatek, int value) {
	//Tworzenie nowego obiektu
	List_1* nowy = new List_1{ value, poczatek };
	poczatek = nowy;
}

void addAfter(List_1 * &poczatek, int valueToInsertAfter, int value) {
	List_1* current = find(poczatek, valueToInsertAfter);

	//Zamiana wskaünikÛw
	if (current) {
		List_1* nowy = new List_1{ value, current->nastepny };
		current->nastepny = nowy;
	}
	else {
		cout << "Nie ma elementu o wartosci: " << valueToInsertAfter << endl;
	}
}

void addToBack(List_1 * &poczatek, int value) {
	//Jeøeli lista jest pusta
	if (!poczatek) {
		poczatek = new List_1{ value, nullptr };
		return;	//Konczymy funkcje
	}	//W przeciwnym wypadku dodajemy nowy element za ostatnim na liscie

	List_1* koniec = poczatek;
	//Przejscie na koniec listy
	while (koniec->nastepny != nullptr) {
		koniec = koniec->nastepny;
	}
	//Dodanie elementu
	koniec->nastepny = new List_1{ value, nullptr};
}

void removeFromFront(List_1 * &poczatek) {
	if (!poczatek) {
		cout << "Lista jest pusta, nie ma nic do usuniecia" << endl;
	}else {
		List_1* tmp = poczatek;
		poczatek = poczatek->nastepny;
		delete tmp;
	}
}

void removeFromBack(List_1 * &poczatek) {
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

void removeAfter(List_1 * &poczatek, int value) {
	List_1* current = find(poczatek, value);
	
	if (current) {	//Jezeni lista nie jest pusta
		if (current->nastepny == nullptr) {	//Jezeli to ostatni element
			delete current;
			current = nullptr;
		}
		else {
			List_1* tmp = current->nastepny;
			current = tmp->nastepny;
			delete tmp;
		}
	}else {
		cout << "Nie ma elementu o wartosci: " << value << endl;
	}
}

void removeFind(List_1* &poczatek, int value) {
	List_1* szukana = poczatek;	//Szukana wartosc
	List_1* poprzedni = NULL;	//Element na liscie przed szukanym

	if (!szukana) {	//Lista musi istaniec inaczej current = nullprt
		cout << "Nie ma tekiego elementu na liscie. Usuwanie nie powiodlo sie." << endl;
		return;
	}

	//Szukanie elementu po ktorym wartosc ma zostac dodana
	while (szukana && (szukana->wartosc != value)) {	//Kolejnosc warunku ma znaczenie
		poprzedni = szukana;
		szukana = szukana->nastepny;
	}
	// Jeúli element nie zosta≥ znaleziony w liúcie
	 if (poczatek->wartosc == value) {
		// Jeúli element do usuniÍcia jest na poczπtku listy
		poczatek = szukana->nastepny;
		delete szukana;
		return;
	}else {
		// UsuÒ element ze úrodka lub koÒca listy
		poprzedni->nastepny = szukana->nastepny;
		delete szukana;
	}
}