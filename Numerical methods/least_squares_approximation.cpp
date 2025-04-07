#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Funkcja do obliczania aproksymacji liniowej metod� najmniejszych kwadrat�w
void linearApproximation(double **points, double& a, double& b, int size, double &R) {
    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0, sum_y2 = 0;

    // Obliczanie sum potrzebnych do obliczenia wsp�czynnik�w a i b
    for (int i = 0; i < size; ++i) {    //Przejscie przez wszystkie punkty
        sum_x += points[i][0];
        sum_y += points[i][1];
        sum_x2 += pow(points[i][0], 2);
        sum_y2 += pow(points[i][1], 2);
        sum_xy += points[i][1] * points[i][0];
    }

    // Obliczanie wsp�czynnik�w a i b wedlug wzoru
    a = (size * sum_xy - sum_x * sum_y) / (size * sum_x2 - pow(sum_x, 2));
    b = (sum_y * sum_x2 - sum_x * sum_xy) / (size * sum_x2 - pow(sum_x, 2));

   // Oblicznie wsp�czynnika korelacji R, gdzy wynosi -1 lub 1 to wyniki dopasowania jest bardzo dobry gdzy 0 to przeciwnie
    R = (size * sum_xy - sum_x * sum_y)/(sqrt(size * sum_x2 - pow(sum_x, 2)) * sqrt(size * sum_y2 - pow(sum_y,2)));
}

int main() {
    //Aproksymacja metoda najmniejszych kwadrat�w - regresja liniowa
    //obliczanie wsp�czynnikow a i b aproksymacji liniowej metod� najmniejszych kwadrat�w dla zestawu danych wej�ciowych x i y

    //Odczyt danych punkt�w dla kt�rych szukamy funkcji 
    int size;
    fstream read("MN3.txt");

    if (read.is_open()) {
        read >> size;   // Liczba punkt�w
        cout << "The number of points for which we complete the task: " << size << endl;

        double** points = new double* [size];   // Tablica wska�nik�w

        // Alokacja pami�ci dla ka�dej tablicy wewn�trznej
        for (int i = 0; i < size; i++) {
            points[i] = new double[2];
        }

        // Odczytanie danych do tablicy dwuwymiarowej
        for (int i = 0; i < size; i++)
            read >> points[i][0] >> points[i][1];

        cout << "Print points" << endl;
        for (int i = 0; i < size; i++)
            cout << "X: " << points[i][0] << " Y: " << points[i][1] << endl;

        //Deklaracja wartosci a, b, kt�rych szukamy
        double a, b, R;

        linearApproximation(points, a, b, size, R);    //Dla szukanej y=ax+b

        if(b > 0)
            cout << "y=" << a << "*x+" << b << endl;
        else if (b == 0)
            cout << "y=" << a << "*x" <<  endl;
        else
            cout << "y=" << a << "*x" << b << endl;

        // Wsp�czynnik korelacji R
       cout << "R: " << R << endl;

        // Zwolnienie pami�ci
        for (int i = 0; i < size; i++) {
            delete[] points[i];
        }
        delete[] points;
    }
    else
        cout << "Failed to open the file :<" << endl;

    read.close();

    system("PAUSE");
    return 0;
}