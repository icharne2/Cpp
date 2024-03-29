#include <iostream>
#include <string>

using namespace std;

const int MAX_CHAR = 256;   // jako maksymalna liczba mo¿liwych znaków, jakie mog¹ wyst¹piæ w tekœcie na podstawie ASCII

// Funkcja obliczaj¹ca automat skoñczony dla danego wzorca
void buildFSM(const string& pattern, int M, int** fsm) {
    fsm[0][pattern[0]] = 1;  // Inicjalizacja pierwszej krawêdzi w automacie dla pierwszego znaku wzorca

    int x = 0;          // Zmienna pomocnicza do przechodzenia po automacie
    for (int i = 1; i <= M; ++i) {  // Przechodzimy przez kolejne znaki wzorca
        for (int j = 0; j < MAX_CHAR; ++j) {
            fsm[i][j] = fsm[x][j];      // Kopiujemy stany z poprzedniego wiersza automatu
        }
        if (i < M) {
            fsm[i][pattern[i]] = i + 1;     // Aktualizujemy automat dla kolejnego znaku wzorca
            x = fsm[x][pattern[i]];     // Przechodzimy do poprzedniego stanu w automacie
        }
    }
}

// Funkcja wyszukuj¹ca wzorzec w tekœcie za pomoc¹ automatu skoñczonego
void searchPattern(const string& text, const string& pattern) {
    int M = pattern.length();   //Rozmair wzorca
    int N = text.length();      //Rozmiar tekstu

    // Inicjalizacja automatu skoñczonego (FSM)
    int** fsm = new int* [M + 1];   //Alokacja 2 wymiarowej tablicy

    for (int i = 0; i <= M; ++i) {
        fsm[i] = new int[MAX_CHAR];
        //Alokacja pamiêci dla tablicy stanu automatu
    }

    // Inicjalizacja tablicy stanów
    for (int i = 0; i <= M; ++i) {  //Przechodzi przez wszystkie stany automatu (od 0 do M), w³¹cznie z dodatkowym stanem M, który jest u¿ywany do obs³ugi sytuacji granicznych podczas przetwarzania wzorca.
        for (int j = 0; j < MAX_CHAR; ++j) {    //Przechodzi przez wszystkie mo¿liwe znak
            fsm[i][j] = 0;  //Wyczyszczenie tablicy stanow - brak przejœcia do innych stanów.
        }
    }

    // Budowa automatu skoñczonego
    buildFSM(pattern, M, fsm);

    // Wyszukiwanie wzorca w tekœcie
    int state = 0; // Pocz¹tkowy stan automatu
    int occurrences = 0; // Licznik wyst¹pieñ wzorca

    for (int i = 0; i < N; ++i) {
        state = fsm[state][text[i]];    // Przechodzenie do kolejnego stanu w automacie
        if (state == M) {   //Sprawdza, czy wzorzec zosta³ znaleziony
            cout << "Znaleziono wzorzec na indeksie: " << i - M + 1 << endl;
            state = fsm[state][pattern[M - 1]]; // Przesuniêcie do kolejnego pasuj¹cego fragmentu

            occurrences++;  //inkrementacja licznika wyst¹pieñ wzorca
        }
    }

    cout << "Liczba wystapien wzorca: " << occurrences << endl;

    // Zwolnienie pamiêci
    for (int i = 0; i <= M; ++i) {
        delete[] fsm[i];
    }
    delete[] fsm;
}


int main() {
    string text = "ABABABACABA";
    string pattern = "ABABACA";

    searchPattern(text, pattern);

    system("PAUSE");
    return 0;
}
