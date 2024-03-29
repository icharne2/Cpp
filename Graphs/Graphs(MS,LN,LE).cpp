#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

//Struktura - Lista s¹siedztwa grafu
struct Graf1 {
	int value;	 // Wierzcho³ek koñcowy krawêdzi
	int dystans; // Waga krawêdzi
	Graf1* next;  // WskaŸnik na nastêpn¹ krawêdŸ w liœcie s¹siedztwa
};

void Add(Graf1*& head, int value, int dystans) {
	Graf1* newNode = new Graf1;
	newNode->value = value+1;
	newNode->dystans = dystans;
	newNode->next = head;
	head = newNode;
}

void show(Graf1* head, int from) {
	cout << "LN[" << from << "]->";
	Graf1* current = head;
	while (current) {
		cout << current->value << "/" << current->dystans;
		if (current->next) {
			cout << "->";
		}
		else {
			cout << "->NULL;";
		}
		current = current->next;
	}
	cout << endl;
}

//Struktura - Lista krawêdzi grafu
struct Graf2 {
	int dokad;		// Wierzcho³ek koñcowy krawêdzi
	int skad;		//Wierzcholek poczatkowy
	int dystans;	// Waga krawêdzi
	Graf2* next;	// WskaŸnik na nastêpn¹ krawêdŸ w liœcie s¹siedztwa
};

void Add2(Graf2*& head, int skad, int dokad, int dystans) {
	Graf2* newNode = new Graf2;
	newNode->skad = skad+1;
	newNode->dokad = dokad+1;
	newNode->dystans = dystans;
	newNode->next = head;
	head = newNode;
}

void show2(Graf2*& LE, int rozmiar) {
	for (int i = 1; i <= rozmiar; i++) {
		cout << "LE[" << i << "]->";

		Graf2* current = LE;
		while (current) {
			if (current->skad  == i) {
				cout << current->dokad  << "/" << current->dystans ;
				if (current->next && current->next->skad == i )	cout << "->";
				else cout << "->NULL";
			}current = current->next;
		}
		cout << endl;
	}
}

int main() {
	fstream czytaj;
	int rozmiar;

	czytaj.open("graf.txt");
	czytaj >> rozmiar;

	//Tworzenie tablicy 2 wymiarowej
	int** M = new int* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		M[i] = new int[rozmiar];

	//Uzupelnienie wartosciami tabliczy 2 wymiarowej
	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++)
			czytaj >> M[i][j];

	//Zamkniecie pliku, z ktorego czytalismy dane
	czytaj.close();

	//Wypisanie tablicy 2 wymiarowej -> MN - macierz sasiedztwa grafu
	cout << "Macierz sasiedztwa o rozmiarze: " << rozmiar << "." << endl;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++)
			cout << M[i][j] << " ";
		cout << endl;
	}

	//LN - lista s¹siedztwa grafu
	cout << "Lista sasiedztwa o rozmiarze: " << rozmiar << "." << endl;

	//Tworzenie listy wskaŸników o rozmiarze grafu - 8
	Graf1** LN = new Graf1 * [rozmiar];
	for (int i = 0; i <= rozmiar; i++)
		LN[i] = NULL;

	//Przejœcie po liœcie i tworzenie wskaŸników do ka¿dego head'a
	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++)
			if (M[i][j] != 0)
				Add(LN[i], j, M[i][j]);

	//Wypisanie listy
	for (int i = 0; i < rozmiar; i++)
		show(LN[i], i+1);
	
	//LE - Lista krawedzi grafu
	cout << "Lista krawedzi grafu o rozmiarze: " << rozmiar << "." << endl;
	
	//Tworzenie pocz¹tku listy
	Graf2* LE = NULL;
	Graf2* LE2 = NULL;

	//1. Generowanie LE w oparciu o MN
	
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (M[i][j] != 0) {
				Add2(LE, i, j, M[i][j]);
			}
		}
	}

	//Wypisanie
	cout << "Wypisanie po wygenerowaniu w oparciu o MN" << endl;
	show2(LE, rozmiar);

	//2. Generowanie LE w oparciu o LN
	cout << "Wypisanie po wygenerowaniu w oparciu o LN" << endl;

	for (int i = 0; i < rozmiar; i++) {
		Graf1* current = LN[i];
		while (current) {
			Add2(LE2, i, current->value - 1, current->dystans);
			current = current->next;
		}
	}

	//Wypisanie
	show2(LE2, rozmiar);

	//3. Generowanie LN w oparciu o LE
	cout << "Wypisanie LN po wygenerowaniu w oparciu o LE" << endl;

	//Nowa tablica wskaŸników na struktury
	Graf1** LNfromLE = new Graf1 * [rozmiar];
	for (int i = 0; i <= rozmiar; i++)
		LNfromLE[i] = NULL;

	Graf2* currentLE = LE;	//Pomocnicza zmienna s³u¿aca do przejscia po liœcie LE
	while (currentLE) {
		Add(LNfromLE[currentLE->skad - 1], currentLE->dokad - 1, currentLE->dystans);
		currentLE = currentLE->next;
	}

	// Wypisanie listy
	for (int i = 0; i < rozmiar; i++)
		show(LNfromLE[i], i + 1);


	system("PAUSE");
	return 0;
}