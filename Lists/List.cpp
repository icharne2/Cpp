#include <iostream>

using namespace std;

struct Node {
	int value;		//Wartosc
	Node * next;	//WskaŸnik na nastepny element listy
};

//Funkcja powsta³a aby nie powtarzaæ kodu pare razy
void Add(Node *&Element, int x) {
	Element = new Node;	//Tworzenie nowej "szufladki"
	Element->value = x;	//Przypisanie do miejsca wartoœci
	Element->next = NULL;	//Przypisanie null jako wska¿nik na nastepny element listy
}

void AddToEnd(Node *&Head, int x) {
	if (Head == NULL) {	//Gdy nie ma ¿adnego elementu w liœcie
		Add(Head, x);
	}
	else {
		Node* pom = Head;	//WskaŸnik pomocniczy ustawiony na pierwszy element listy
		while (pom->next != NULL) {	//Dopuki bêdzie ista³ wskaŸnik na nastêpny elemet bêdziemy zmieniac zmienna pom
			pom = pom->next;	//Zmiana na nastepny element listy
		}
		Add(pom->next, x);	//Dodanie nowego elementu listy na koniec
	}
}

void AddToStart(Node *&Head, int x) {
		Node* pom = new Node; //Szufladka pomocnicza
		pom->value = x;		//Przypisanie do nowego elementu wartosci
		pom->next = Head;	//Wskazanie nastepnego elementu (naszej poprzedniej g³owy)
		Head = pom;			//Nasz¹ nowa¹ g³ow¹ jest teraz pom który ma wska¿nik na star¹ g³owê	
}

//Dodanie za element
void AddAfter(Node *&Element, int x) {
	Node* pom = new Node;
	pom->next = Element->next;
	pom->value = x;
	Element->next = pom;
}

void Remove(Node*& Head, int x) {
	if (Head != NULL) {	//Sprawdzenie, czy istanieje jakis elemet tablicy
		Node* pom = Head; //Zmienna pomocnicza s³u¿¹ca do przejscia po liœcie
		Node* prev = nullptr;	//Pusty wskaznik do przetrzymywania poprzedniego elementu

		while (pom && pom->value != x) {	//Szukanie elementu do usuniecia
			prev = pom;
			pom = pom->next;
		}

		if (pom) {  // Znaleziono element do usuniêcia
			if (prev) {	//Jezeli istnieje element poprzedzajacy ten ktory chcemy usunac
				prev->next = pom->next;
			}
			else {
				Head = pom->next;
			}
			delete pom;
		}
	}
}

void RemoveToStart(Node*& Head) {
	if (Head) {
		Node* pom = Head;
		Head = pom->next;
		delete pom;
	}
}

void RemoveAfter(Node *&Head, int x) {  //Zapis *& --> chcemy znac adres wskaznika 
	if (Head != NULL) {	//Sprawdzenie, czy istanieje jakis elemet tablicy
		Node* pom = Head; //Zmienna pomocnicza s³u¿¹ca do przejscia po liœcie
		while (pom && pom->value != x) {
			pom = pom->next;
		}
		if (pom && pom->next) {
			Node* e = pom->next;
			pom->next = e->next;
			delete e;
		}
	}
}

void UsunCoDrugi(Node* Head) {
	if (Head) {
		Node* pom = Head;
		while (pom) {
			if (pom->next) {
				Node* e = pom->next;
				pom->next = e->next;
				delete e;
				pom = pom->next;
			}
		}
	}
}

void KopiaListy(Node*& Head) {
	if (Head) {
		Node* pom = Head;
		while (pom) {
			AddAfter(pom, pom->value);
			pom = pom->next->next;
		}
	}
}

//Kopia Ca³ej listy H->1->2   ==>  H->1->2->1->2
void KopiaCalejListy(Node*& Head) {
	if (Head) {	//Jezeli istnieje lista
		Node* pom = Head;
		Node* NewHead = NULL;	

		while (pom->next) {	//Dopoki istnieje element nastepny
			AddToEnd(NewHead, pom->value);	//Dodajemy na koniec 
			pom = pom->next;	//Przechodzimy o element dalej
		}

		AddToEnd(NewHead, pom->value);
		pom->next = NewHead;
	}
}

float LiczSrednia(Node* Head) {
	if (Head) {
		int count = 0;
		float avg = 0.;
		Node* pom = Head;
		while (pom) {
			count++;
			avg += pom->value;
			pom = pom->next;
		}
		return avg / count;
	}
}

void ZamianaNastepnik(Node*& Head, int x) {
	if (Head) {
		Node* current = Head;	//Zmienna pomocnicza do znalezenia elementu
		Node* prev = nullptr;	//Zmienna poprzedzajaca szukany element
		int count = 1;			//Licznik 

		while (current && count != x) {		//Szukanie elementu
			prev = current;
			current = current->next;
			count++;
		}

		// Zamiana elementu x z jego nastêpnikiem
		if (current && current->next) {
			Node* tmp = current->next;	//Zmienna pomocnicza
			current->next = tmp->next;
			tmp->next = current;
			if (prev) {	//Je¿eli istanieje element poprzedzaj¹cy
				prev->next = tmp;
			}
			else {	//Jezeli nasz szukany element to g³owa listy
				Head = tmp;
			}
		}
	}
}

void UsunParzyste(Node*& Head) {
	if (Head) {
		Node* pom = Head;	//Zmienna pomocnicza - obecny obiekt
		Node* prev = nullptr; //Zmiena przechowuj¹ca poprzedni element
		while (pom) {
			if (pom->value % 2 == 0) {	//Szukanie wartoœci podzielnej przez 2
				if (prev) {	//Je¿eli przed szukanym elementem istnieje jakis
					prev->next = pom->next;
				}
				else {	//Jezeli szukany element to g³owa listy
					Head = pom->next;
				}
				delete pom;	//Usuwamy element ktory znalezlismy
				pom = prev->next;	//Przestawiamy obecny element na nastepny ktory zapisany jest w prev->next
			}
			else {
				prev = pom;		//Jezeli nie usuwamy elementu to przechodzimy "zwyczajnie" po liscie
				pom = pom->next;
			}
		}
	}
}

void ZamianaMiejsc(Node *&Head) {	//Do poprawy z³o¿onosc n^2
	if (Head) {
		Node* pom = Head;
		int count = 1;
		while (pom) {
			if (count % 2 != 0) {
				ZamianaNastepnik(Head, count);
			}
			count++;
			pom = pom->next;
		}
	}
}

//Zamiana o innej z³o¿onoœci - wydajniejszej
void ZamianaMiejsc2(Node*& Head) {
	Node* pom = new Node;	//Zmienna pomocnicza, która bedzie przechowywac Head
	//Bez tej zmiennej utrata g³owy listy spowodowa³aby, ¿e nie bylibyœmy w stanie 
	//dostêpu do pocz¹tku listy po jej modyfikacji
	pom->next = Head;
	Head = pom;

	Node* tmp = Head;	//Zmienna pomocniczna potrzebna do zamiany

	while (tmp->next != NULL && tmp->next->next != NULL)
	{
		Node* a = tmp->next;
		Node* b = tmp->next->next;
		Node* c = tmp->next->next->next;

		tmp->next = b;
		b->next = a;
		a->next = c;

		tmp = a;
	}

	Head = Head->next;
	delete pom;
}

//Wypisanie listy
void PrintList(Node *&Head) {	//Funkcja wypisuj¹ca wszystkie elementy listy
	if (Head != NULL) {
		Node *pom = Head;	//Zmienna pomocnicza, s³u¿¹ca do przejœcia przez listê
		while (pom) {	//Do wypisania wszytskich elementów
			cout << pom->value << " ";
			pom = pom->next;
		}
	}
	else {
		cout << "Lista jest pusta :< ";
	}
	cout << endl;
}

// Wykonaj kopie H->1->2->3 ==> H->1->2->3->3->2->1
void KopiaListy2(Node*& Head) {
	if (Head) {	//Jezeli istnieje lista
		Node* Head2 = NULL;	
		Node* pom = Head;

		while (pom->next) {	//Tak aby stac na ostatnim elemencie
			AddToStart(Head2, pom->value);
			pom = pom->next;
		}
		AddToStart(Head2, pom->value);	//Ostatni element nie spe³niaj¹cy while poniewa¿ nie ma next
		pom->next = Head2;
	}
}

void PodzialNaPolowe(Node *&Head, Node *&Head1, Node *&Head2) {
	if (Head) {
		Node* obecny = Head;	//Obecny element to g³owa poczatkowej listy
		Node* nastepny = Head->next;	//WskaŸnik na nastepny element 

		while (nastepny) { //Jezeli element dalej istneieje
			nastepny = nastepny->next;	//Przesuwamy sie o jeszcze jeden
			if (nastepny) {	//Jezeli isnieje 3 w kolejnosci element
				obecny = obecny->next;	
				nastepny = nastepny->next;
			}
		}
		//Po wyjœciu z petli while obecny wskazuje na po³owe listy
		Head1 = Head;	//Pierwsza polowa ma head jak poczatkowa
		Head2 = obecny->next;		//Nowa lista Head2 bedzie mia³a swoj poczatek w po³owie listy
		obecny->next = nullptr;		//Usuwamy po³¹czenie miedzy ostatnim elementem Head1 a 1 g³ow¹ Head2
	}
}

void Polaczenie2PosortowanychList(Node*& Head, Node* Head1, Node* Head2) {
	Node* pom1 = Head1;
	Node* pom2 = Head2;

	// Inicjalizacja wskaŸnika na aktualny element w nowej liœcie
	Node* current = nullptr;

	// Dopóki obie listy maj¹ elementy
	while (pom1 && pom2) {
		if (pom1->value <= pom2->value) {	//	Sprawdzamy wartosci
			// Do³¹czanie elementu z listy 1
			if (!current) {
				Head = pom1;  // Jeœli to pierwszy element, ustaw go jako g³owê
				current = Head;
			}
			else {
				current->next = pom1;
				current = current->next;
			}
			pom1 = pom1->next; //	p	rzechodzimy o jeden element dalej
		}
		else {
			// Do³¹czanie elementu z listy 2
			if (!current) {
				Head = pom2;  // Jeœli to pierwszy element, ustaw go jako g³owê
				current = Head;
			}
			else {
				current->next = pom2;
				current = current->next;
			}
			pom2 = pom2->next;
		}
	}

	// Do³¹czenie pozosta³ych elementów z listy Head1
	if (pom1) {
		if (!current) {
			// Jeœli lista jest pusta, ustaw g³owê na pierwszy element z Head1
			Head = pom1;
		}
		else {
			// Jeœli lista nie jest pusta, do³¹cz pozosta³e elementy z Head1 na jej koniec
			current->next = pom1;
		}
	}

	// Do³¹czenie pozosta³ych elementów z listy Head2
	if (pom2) {
		if (!current) {
			Head = pom2;
		}
		else {
			current->next = pom2;
		}
	}
}

void sortowanieBabelkowe(Node*& Head) {
	if (Head) {	//Sortowanie wykona sie jezeli lista istnieje
		Node* pom = Head;
		Node* tmp = NULL;

		//Wykonanie petli w celu ustawienia tmp
		while (pom && pom->next) {
			if (pom->value > pom->next->value) {
				ZamianaMiejsc(pom);
				tmp = pom;
			}
		}
	}

}

int main() {
	Node *Head = NULL;	//Tworzenie "szuflaki" - wskaznik na 1-szy element, pocz¹tkowo jest pusty
	
	/*AddToStart(Head, 4);
	AddToStart(Head, 3);
	AddToStart(Head, 2);
	cout << "Lista poczatkowa:" << endl;
	PrintList(Head);*/
	
	//Zadanie 1. Usuñ co drugi element na liœcie
		/*UsunCoDrugi(Head);
		cout << "Lista po usunieciu co 2 elementu: " << endl;
		PrintList(Head);
		*/

	//Zadanie 2. Kopia listy H->1->3->...  ==>  H->1->1->3->3->...
		/*cout << "Lista po dokonaniiu kopi co element:" << endl;
		KopiaListy(Head);
		PrintList(Head);
		*/

	//Zadanie 3. Kopia Ca³ej listy H->1->2   ==>  H->1->2->1->2
		/*cout << "Lista po calkowitej duplikacji" << endl;
		KopiaCalejListy(Head);
		PrintList(Head);
		*/

	//Zadanie 4. Oblicz œredni¹ elementów na liœcie
		/*float result = 0.;
		cout << "Œrednia elementow znajdujacych sie w liscie:" << endl;
		result = LiczSrednia(Head);
		cout << result << endl;
		*/

	//Zadanie 5. Zamieñ element x ze swoim nastêpnikiem
		/*cout << "Lista po zamianie x elementu ze swoim nastêpnikiem." << endl;
		ZamianaNastepnik(Head, 1);
		PrintList(Head);
		*/

	//Zadanie 6. Usuñ elementy parzyste z listy
		/*cout << "Lista po wykonaniu usuniec wartosci parzystych:" << endl;
		UsunParzyste(Head);
		PrintList(Head);
		*/

	//Zadanie 7. Zamieñ miejscami co 2 element listy.
		/*cout << "Lista po zamianie 2 miejscami." << endl;	//Zlozonosc n^2
		ZamianaMiejsc(Head);
		PrintList(Head);
		*/

	//Zadanie 7. Inna metoda i lepszej z³o¿onoœci
		/*cout << "Lista po zamianie 2 miejsc przez calosc - metoda 2" << endl;
		ZamianaMiejsc2(Head);
		PrintList(Head);
		*/

	//Zadanie 8. Wykonaj kopie H->1->2->3 ==> H->1->2->3->3->2->1
		/*cout << "Wykonanie kopi listy" << endl;
		KopiaListy2(Head);
		PrintList(Head);
		*/
		
	//Zadanie 9. Podziel liste na pó³
		/*Node* Head1 = NULL;
		Node* Head2 = NULL;

		cout << "Podzielenie listy na polowe" << endl;
		PodzialNaPolowe(Head, Head1, Head2);

		cout << "Lista 1 po podzieleniu:" << endl;
		PrintList(Head1);
		cout << "Lista 2 po podzieleniu:" << endl;
		PrintList(Head2);
		*/
	//Zadanie 10. Po³¹cz dwie posortowane listy ze soba
		cout << "Laczenie list ze soba" << endl;
		Node* Head1 = NULL;
		AddToStart(Head1, 4);
		AddToStart(Head1, 3);
		AddToStart(Head1, 2);
		AddToStart(Head1, 1);

		Node* Head2 = NULL;
		AddToStart(Head2, 4);
		AddToStart(Head2, 3);
		AddToStart(Head2, 2);
		AddToStart(Head2, 1);

		Polaczenie2PosortowanychList(Head, Head1, Head2);
		PrintList(Head);
		
	system("PAUSE");
	return 0;
}