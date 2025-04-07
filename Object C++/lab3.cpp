#include<iostream>
#include<string>

using namespace std;

namespace Biblioteczka {
	class Ksiazka {
	private:
		string tytul;
		string autor;
		int rok_wydania;
		static int licznik;

	public:
		// Default constructor
		Ksiazka() {
			cout << "Ksiazka zostala utworzona" << endl;
			tytul = "Brak";
			autor = "Brak";
			rok_wydania = 0;
			licznik++;
		}

		// Parameterized constructor
		Ksiazka(string t, string a, int r) : tytul(t), autor(a), rok_wydania(r) {
			licznik++;
		}

		void zmienTytul(string tyt) {
			this->tytul = tyt;
		}

		void zmienAutora(string aut) {
			this->autor = aut;
		}

		void zmienRok(int rok) {
			this->rok_wydania = rok;
		}

		bool czyXXwiek() {	// checks if the book was published in the 20th century
			if (this->rok_wydania >= 1900 && (this->rok_wydania < 2000)) {
				return true;
			}
			else {
				return false;
			}
		}

		int pokazRok() {
			return rok_wydania;
		}

		void wyswietl() {
			cout << "Tytul: " << tytul << endl;
			cout << "Autor: " << autor << endl;
			cout << "Rok wydania: " << rok_wydania << endl;
		}

		// Static methods to edit the counter

		static int getLicznik() {
			return licznik;
		}

		static void setLicznik(int nowyLicznik) {
			licznik = nowyLicznik;
		}
	};

	int Ksiazka::licznik = 0;
}

//  Sorting function for books by publication year (descending)
void sortowanieRok(Biblioteczka::Ksiazka tab[], int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 1; j < n - i; j++)
			if (tab[j - 1].pokazRok() < tab[j].pokazRok())
				swap(tab[j - 1], tab[j]);
}

int main() {
	//A)Create one book + an array of 4 books
	Biblioteczka:: Ksiazka ksiazka_1;

	ksiazka_1.zmienAutora("Maly ksiaze");
	ksiazka_1.zmienTytul("Antoine de Saint-Exupery");
	ksiazka_1.zmienRok(1943);

	Biblioteczka::Ksiazka ksiazki[4] = {
		Biblioteczka::Ksiazka("W pustyni i w puszczy", "Henryk Sienkiewicz", 1912),
		Biblioteczka::Ksiazka("Pan Tadeusz", "Adam Mickiewicz", 1834),
		Biblioteczka::Ksiazka("Lalka", "Boleslaw Prus", 1890),
		Biblioteczka::Ksiazka("Ferdydurke", "Witold Gombrowicz", 1937)
	};

	cout << "\nDane ksi¹¿ek:\n";
	for (int i = 0; i < 4; i++) {
		ksiazki[i].wyswietl();
	}

	//B) Check if books are from the 20th century
	for (int i = 0; i < 4; i++) {
		if (ksiazki[i].czyXXwiek()) {
			cout << "Book was published in the 20th century." << endl;
		}
		else {
			cout << "Book was NOT published in the 20th century." << endl;
		}
	}
	cout << endl;

	//C) Sort books by year in descending order
	sortowanieRok(ksiazki, 4);

	// Display the sorted array
	for (int i = 0; i < 4; i++) {
	for (int i = 0; i < 4; i++) {
		ksiazki[i].wyswietl();
	}
	cout << endl;

	//D)
	// Biblioteczka::Ksiazka::setLicznik(4); // Overwrite the counter (optional)

	cout << "Number of books in the system: " << Biblioteczka::Ksiazka::getLicznik() << endl;

	return 0;
}