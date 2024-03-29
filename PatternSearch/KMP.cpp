#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void stworzTabliceDopasowan(string znajdzWzor, int*& tabDopasowania) {
    int a = 0;  //bêdzie u¿ywana do œledzenia iloœci znaków dopasowanych w danym momencie pref-suf

    //tablica czêœciowych dopasowañ o rozmiarze równym liczbie znaków szukanego tekstu
    tabDopasowania = new int[znajdzWzor.size()];
    tabDopasowania[0] = 0;

    //Zmienna pomocnicza do przejsc w tablicy
    int i = 1;  

    while (i < znajdzWzor.size()) { //Gdy 
        if (znajdzWzor[i] == znajdzWzor[a]) {   //Gdy znaleziono kolejny znak pasuj¹cy do wzorca
            a++;    //Zwiêkszenie dlugosci aktualnego pref-suf
            tabDopasowania[i] = a; //Przepisywanie do tablicy aktualnej dlugosci dopasowanych znakow
            i++;    //Przejscie do nastepnego elementu w tablicy wzorca
        }
        else {
            if (a != 0) //  Gdy dlugosc znakow dopasowanych nie jest 0 (pref-suf)
                a = tabDopasowania[a - 1]; //Przesuniêcie do poprzedniego pred-suf
            else {  //Gdy jest a == 0
                tabDopasowania[i] = 0; // Ustaw dlugosc dla obecnej pozycji na 0
                i++;    //Przejdz na nastepny element w tab wzorca
            }
        }
    }
}

void KnuthMorrisPratt(string znajdzWzor, string tekst) {

    int* tabDopasowania = nullptr; //WskaŸnik na tablice dopasowañ
    stworzTabliceDopasowan(znajdzWzor, tabDopasowania);

    int i = 0;  //Zmienna pomocnicza do przechodzenia po kazdej literce w tekscie szukanym
    int j = 0;  //Zmienna pomocnicza dzieki ktorej liczymy ilosc znakow, ktore sie zgadzaja

    while (i < tekst.size()) {  //  Dopoki ilosc znakow w tekscie jest mniejsza od wzorca
        if (znajdzWzor[j] == tekst[i]) { //Jeœli znaleziono znak w tekœcie pasuj¹cy do wzorca
            i++;    //Kolejny znak w takscie
            j++;    //Kolejny znak we wzorcu (znajdz)
        }
        if (j == znajdzWzor.size()) {   //Je¿eli znajdziemy cale slowo szukane
            cout << "Znaleziono wzorzec na pozycji: " << i - j << endl; //i-j ¿eby wiedziec gdzie sie zaczyna
            j = tabDopasowania[j - 1]; //Przesuwamy indeks w tablicy dopasowan na poprzedni element
        }else if (i < tekst.size() && znajdzWzor[j] != tekst[i]) {  //Znaleziono niepasujacy znak
                if (j != 0)     j = tabDopasowania[j - 1]; //Jezeli nie jestesmy na poczatku wzorca. Przesuwamy indeks wzorca na poprzedni w tablicy dopasowan
                else    i++;    // Nastepny znak w tekscie
        }
    }

    delete[] tabDopasowania;   // Zwolnienie pamieci dla tablicy dopasowan LPS
}

int main() {
    cout << "Szukanie wzorca w 1 tekscie" << endl;
    KnuthMorrisPratt("ABABD", "ABABCABCABABABD"); //W napisie AGHAAGAAHAA szukamy wzorca AHA

    string text, wzor;

    cout << "Podaj tekst." << endl;
    cin >> text;

    cout << "Podaj wzorzec." << endl;
    cin >> wzor;

    KnuthMorrisPratt(wzor, text);

    system("PAUSE");
    return 0;
}
