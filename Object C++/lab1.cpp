#include<iostream>
using namespace std;

int *doubleValue(int array[], int size) {
	int* result = new int[size];

	for (int i = 0; i < size; i++) {
		result[i] = array[i] * 2;
	}

	return result;
}

struct Batonik {
	string marka = "null";
	float waga = 0.;
	int kcal = 0;
};

int main() {
	/*
	Stwórz tablicę liczb całkowitych o rozmiarze 100. Kolejne elementy tablicy powinny mieć
	wartości o jeden większe od poprzedniego elementu.Pierwszy element powinien mieć
	wartość 0. Sprawdź, czy dziesiąty element tablicy jest podzielny przez dwa.Stwórz wskaźnik
	i ustaw go na 11 - tym elemencie tablicy.Wyświetl ten element przy użyciu wskaźnika
	*/

	int array[100];

	for (int i = 0; i < 100; i++) {
		array[i] = i;
	}

	if (array[9] % 2 == 0) {	//9, poniewaz tablice numerowane od 0
		cout << "10 element tablicy jest podzielny przez 2." << endl;
	}
	else {
		cout << "10 element tablicy nie jest podzielny przez 2." << endl;
	}

	int* wsk = &array[10];	//10, poniewaz tablice numerowane od 0
	cout << "11 element tej tablicy to: " << *wsk << endl;

	/*
	Napisz funkcję, która przyjmie czteroelementową tablicę liczb całkowitych i zwróci nową
	tablicę z podwojoną każdą wartością.
	przykład:
	wejście: {1, 6, -7, 3}
	wyjście: {2, 12, -14, 6}
	*/

	int array2[] = {1, 6, -7, 3};
	int size = 4;
	int *arrayNew = doubleValue(array2, size);

	cout << "Tablica po zmianie " << endl;
	for (int i = 0; i < size; i++) {
		cout << arrayNew[i] << " ";
	}cout << endl;

	/*
	Struktura „Batonik” ma trzy pola. Pierwsze to marka słodyczy, drugie to waga
	(z uwzględnieniem części ułamkowej), a trzecie to liczba kalorii (liczba całkowita). Napisz
	program deklarujący taką strukturę i tworzący zmienną typu „Batonik” o nazwie snack,
	inicjalizując poszczególne pola wartościami „Bounty”, 57, 278. Program powinien na sam
	koniec wyświetlić zawartość zmiennej snack.
	*/
	struct Batonik snack = { "Bounty", 57., 278 };

	cout << "Batonik: " << snack.marka << " " << snack.waga << "g " << snack.kcal << "kcal" << endl;

	system("PAUSE");
	return 0;
}
