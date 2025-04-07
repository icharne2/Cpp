#include <iostream>
#include <fstream>

using namespace std;

int main()
{   //Przybli�anie funcji przez wielomian Lagrange'a
    //Jeden z podstawowych wad tego algorytmu - nie mo�na dok�ada� bez liczenia nie od pocz�tku kolejnego punktu (w�z�a)
    
    //Przebieg:
    //Definiujemy - ilosc punkt�w 
    //Podaj punkty wsp�rzednych x,y
    //Punkt gdzie szukamy warto�� w danym punkcje np. x=4 - punkt szukany lub seria punkt�w
    //Parametr l wyznaczanie - liczenie dla poszczegulnych w�z��w, sk�adnik�w 

    int size;
    fstream read("NM1.txt");

    if (read.is_open()) {
        read >> size;   //Liczba punkt�w
        cout << "Ilosc punktow dla ktorych wykonujemy zadanie: " << size << endl;

        //Tworzenie tablicy dynamicznej dwuwymiarowej, przechowuj�cej wsp�rz�dne punkt�w x, y
        double** points = new double* [size];

        for (int i = 0; i < size; i++)  points[i] = new double[size];

        for (int i = 0; i < size; i++) {
            read >> points[i][0] >> points[i][1];

            cout << "Punkt utworzony M=(" << points[i][0] << ", " << points[i][1] << ")" << endl;
        }
        
        double value;
        cout << "Podaj wartosc X dla ktorego szukamy wartosci Y. " << endl;
        cin >> value;

        double result_y = 0;   //Zmienna przechowuj�ca wynik 

        for (int i = 0; i < size; i++){ // Przechodzimy przez kazdy punkt i liczymy warosci
            double wielomian_l = 1;

            for (int j = 0; j < size; j++){     //obliczanie l(value)
                if (j != i){
                    wielomian_l *= (value - points[j][0]) / (points[i][0] - points[j][0]);    
                }
            }
            result_y += points[i][1] * wielomian_l;   //Wynikiem jest suma warto�ci L(value) = xi * l1(value) + ...
        }
        cout << "Dla podanego x= " << value << " wartosc y wynosi: " << result_y << endl;
        
        for (int i = 0; i < size; ++i)
            delete[] points[i];
        delete[] points;

    }else   cout << "Nie udalo sie otworzyc pliku" << endl;

    read.close();

    system("PAUSE");
    return 0;
}