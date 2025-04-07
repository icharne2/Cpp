#include <iostream>
#include <string>

using namespace std;

// Class representing a car
class Samochod {
private:
    string marka;  // brand
    string model;  // model
    float cena;    // price

public:
    // Default constructor
    Samochod() {}

    // Parameterized constructor
    Samochod(string mar, string mod, float cen) : marka(mar), model(mod), cena(cen) {}

    // Method to print car details
    void wypisz() {
        cout << "Marka: " << marka << endl;
        cout << "Model: " << model << endl;
        cout << "Cena: " << cena << endl;
    }

    // Method that returns the price of the car
    float zwrocCena() {
        return cena;
    }
};

// Class representing a garage
class Garaz {
private:
    string nazwa;                  // name of the garage
    Samochod* samochody[15];      // array of pointers to Samochod objects
    int ilosc = 0;                // current number of cars in the garage

public:
    // Constructor that initializes the garage with a name
    Garaz(string naz) {
        nazwa = naz;
        cout << "Tworzenie garazu: " << nazwa << endl;  // Display garage name
    }

    // Method to add a car to the garage
    void dodajSamochod(Samochod* s) {
        if (ilosc < 15) {
            samochody[ilosc++] = s;
        }
        else {
            cout << "Brak miejsca w garazu " << nazwa << "!" << endl;  // No space left
        }
    }

    // Method to print all cars in the garage
    void wypiszAuta() {
        cout << "Garaz: " << nazwa << endl;
        cout << "Samochody:" << endl;
        for (int i = 0; i < ilosc; i++) {
            samochody[i]->wypisz();
            cout << endl;
        }
    }

    // Method to calculate and display the total value of all cars in the garage
    void wartoscAut() {
        float suma = 0;
        for (int i = 0; i < ilosc; i++) {
            suma += samochody[i]->zwrocCena();
        }
        cout << "Wartosc samochodow w garazu " << nazwa << ": " << suma << endl;
    }
};

int main() {
    // a) Creating two arrays of cars
    Samochod tab1[2] = {
        Samochod("Toyota", "Corolla", 50000),
        Samochod("Honda", "Civic", 60000)
    };

    Samochod tab2[3] = {
        Samochod("BMW", "X5", 150000),
        Samochod("Audi", "A4", 120000),
        Samochod("Ford", "Focus", 45000)
    };

    // Displaying the contents of the first array
    cout << "Tablica 1:" << endl;
    for (int i = 0; i < 2; i++) tab1[i].wypisz();

    // Displaying the contents of the second array
    cout << "Tablica 2:" << endl;
    for (int i = 0; i < 3; i++) tab2[i].wypisz();

    cout << endl;

    // b) Creating two garages
    Garaz garaz1("Gara¿ A");
    Garaz garaz2("Gara¿ B");

    // c) Adding cars from both arrays to the garages
    for (int i = 0; i < 2; i++) garaz1.dodajSamochod(&tab1[i]); // Garage 1 gets cars from tab1
    for (int i = 0; i < 2; i++) garaz2.dodajSamochod(&tab1[i]); // Garage 2 gets cars from tab1
    for (int i = 0; i < 3; i++) garaz2.dodajSamochod(&tab2[i]); // and tab2

    // Displaying garage contents
    garaz1.wypiszAuta();
    garaz2.wypiszAuta();

    // d) Displaying total car values in garages
    garaz1.wartoscAut();
    garaz2.wartoscAut();

    return 0;
}
