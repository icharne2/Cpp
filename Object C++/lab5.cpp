#include<iostream>

using namespace std;

class Pasazer {
private:
    string imie;
    string nazwisko;
    int rok_urodzenia;
    static int licznik; // static field that counts number of existing passengers

public:
    Pasazer() { // default constructor
        this->imie = "Brak";
        this->nazwisko = "Brak";
        this->rok_urodzenia = 0;
        licznik++;
    }

    Pasazer(string i, string n, int r) : imie(i), nazwisko(n), rok_urodzenia(r) { // parameterized constructor
        licznik++;
    }

    Pasazer(const Pasazer& p) { // copy constructor
        this->imie = p.imie;
        this->nazwisko = p.nazwisko;
        this->rok_urodzenia = p.rok_urodzenia;
        licznik++;
    }

    void display() {
        cout << "Name: " << imie << ", Surname: " << nazwisko << ", Year of birth: " << rok_urodzenia << endl;
    }

    static int getCounter() {
        return licznik;
    }

    ~Pasazer() {
        licznik--;
    }
};

// static field initialization
int Pasazer::licznik = 0;

class Autokar {
private:
    string miejsce_docelowe;
    int predkosc_maksymalna;
    const int calkowita_ilosc_miejsc = 20;
    Pasazer* pasazerownie[20]; // array of pointers to passengers
    int licznik = 0;

public:
    Autokar(Pasazer* pasazerowie[], int ilosc_pasazerow, string miejsce_docelowe, int predkosc_maksymalna) {
        this->miejsce_docelowe = miejsce_docelowe;
        this->predkosc_maksymalna = predkosc_maksymalna;

        for (int i = 0; i < ilosc_pasazerow && i < calkowita_ilosc_miejsc; i++) {
            pasazerownie[i] = pasazerowie[i];
            licznik++;
        }
    }

    // copy constructor
    Autokar(const Autokar& other) {
        this->miejsce_docelowe = other.miejsce_docelowe;
        this->predkosc_maksymalna = other.predkosc_maksymalna;
        this->licznik = other.licznik;

        for (int i = 0; i < other.licznik; i++) {
            pasazerownie[i] = new Pasazer(*other.pasazerownie[i]);
        }
    }

    ~Autokar() {
        for (int i = 0; i < licznik; i++) {
            delete pasazerownie[i];
            pasazerownie[i] = nullptr;
        }
    }

    void display() {
        cout << "Destination: " << miejsce_docelowe << endl;
        cout << "Max speed: " << predkosc_maksymalna << endl;
        cout << "Passengers: " << endl;

        for (int i = 0; i < licznik; i++) {
            pasazerownie[i]->display();
        }
    }

    void add(Pasazer* pasazerowie, int size) {
        for (int i = 0; i < size; i++) {
            if (licznik >= calkowita_ilosc_miejsc) {
                cout << "Cannot add more passengers. Seat limit reached." << endl;
                break;
            }
            pasazerownie[licznik] = &pasazerowie[i];
            licznik++;
        }
    }
};


int main() {
    // A) Create 3 passengers
    cout << "Point A)" << endl;
    Pasazer pasazer1; // default constructor
    Pasazer pasazer2("Jan", "Kowalski", 1980); // parameterized constructor
    Pasazer pasazer3 = pasazer2; // copy constructor

    cout << "Number of passengers: " << Pasazer::getCounter() << endl;
    pasazer1.display();
    pasazer2.display();
    pasazer3.display();

    // B) Create dynamic array of passengers
    cout << "Point B)" << endl;
    Pasazer* pasazerowie = new Pasazer[100];

    cout << "Number of passengers: " << Pasazer::getCounter() << endl;

    // C) Create bus and add passengers
    cout << "Point C)" << endl;
    Pasazer* pas[3];
    pas[0] = &pasazer1;
    pas[1] = &pasazer2;
    pas[2] = &pasazer3;

    Autokar autobus(pas, 3, "Warsaw", 100);
    autobus.add(pasazerowie, 100);
    autobus.display();

    // D) Copy constructor for bus
    cout << "Point D)" << endl;
    Autokar autobus2 = autobus;
    autobus2.display();

    // E) Delete dynamically allocated passengers array
    cout << "Point E)" << endl;
    delete[] pasazerowie;
    pasazerowie = nullptr;

    cout << "Number of passengers: " << Pasazer::getCounter() << endl;

    system("pause");
    return 0;
}
