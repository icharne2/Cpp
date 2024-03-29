#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int prime = 101;  // Stała do obliczania hasha, powinna być liczba pierwsza
//Wybór liczby pierwszej jest istotny, ponieważ wpływa na jakość 
//haszowania i minimalizuje możliwość kolizji, czyli sytuacji, gdy różne dane mają ten sam hash.

int hashFunction(string str, int m) {
    int hashValue = 0;  //Obliczona wartosc naszego haszowania

    for (int i = 0; i < m; i++) {
        hashValue = (hashValue * prime + str[i]) % m;   // Obliczanie haszu ze wzoru
    }
    return hashValue;   //zwracamy liczbe hash'u.
}

void RabinKarp(string text, string pattern) {
    int n = text.size();    //Długość tekstu
    int m = pattern.size(); //Długość wzorca

    // Obliczamy liczbe hash dla tekstu i wzorca
    int textHash = hashFunction(text, m);
    int patternHash = hashFunction(pattern, m);

    // Przeszukujemy tekst w poszukiwaniu wzorca
    for (int i = 0; i < n - m + 1; i++) {
        // Sprawdzamy czy hashe są równe, a następnie porównujemy dokładnie
        if (textHash == patternHash) {
            bool match = true;

            //Porownanie znakow
            for (int j = 0; j < m; j++) {
                //Jezeli jednak to nie to slowo
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            //Jezeli slowo zostalo znalezione
            if (match) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Obliczamy hash dla kolejnego okna tekstu
        if (i < n - m) {    //czy nie jesteśmy na końcu tekstu
            textHash = (prime * (textHash - text[i] * int(pow(prime, m - 1))) + text[i + m]) % m;
            //wartość hasza dla danego fragmentu tekstu staje się ujemna po operacji modulo
            if (textHash < 0) {
                //m do wartości hasza, aby poprawić jej wartość i utrzymać ją w akceptowalnych granicach.
                // od 0 do  m−1
                textHash += m;
            }
        }
    }
}

int main() {
    //Algorytm Rabina Karpa
    string text = "This is an example sentence where we are looking for a word.";    // Ciag znakow w ktorym szukamy 
    string pattern = "w";   //Slowo szukane

    //Wywołanie algorytmu 
    RabinKarp(text, pattern);

    return 0;
}
