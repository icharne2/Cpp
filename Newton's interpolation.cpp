#include <iostream>
#include <fstream>

using namespace std;

double differentialQuotient(int size, double **points, int i) {
    if (size == 1)
        return points[i][1];    // Zwracamy Y
    else {
        double quotient = (differentialQuotient(size - 1, points, i + 1) - differentialQuotient(size - 1, points, i)) / (points[i + size - 1][0] - points[i][0]);
        return quotient;
    }
}

double findNewton(int size, double value, double **points) {
    double result_y = 0;   // Zmienna przechowuj¹ca wynik 

    for (int i = 0; i < size; i++) { // Przechodzimy przez ka¿dy punkt i liczymy wartoœci
        double quotient = 1; // pocz¹tkowy iloraz równy 1

        for (int j = 0; j < i; j++) { // obliczanie ilorazów ró¿nicowych
            quotient *= (value - points[j][0]);
        }
        result_y += quotient * differentialQuotient(i + 1, points, 0);   // Wynikiem jest suma wartoœci
    }

    return result_y;
}
int main() {
    // Laboratoria 2 - Przybli¿anie funkcji przez wielomian Newtona

    int size;
    fstream read("NM1.txt");

    if (read.is_open()) {
        read >> size;   // Liczba punktów
        cout << "The number of points for which we complete the task: " << size << endl;

        double** points2 = new double* [size];   // Tablica wskaŸników

        // Alokacja pamiêci dla ka¿dej tablicy wewnêtrznej
        for (int i = 0; i < size; i++) {
            points2[i] = new double[2];
        }

        // Odczytanie danych do tablicy dwuwymiarowej
        for (int i = 0; i < size; i++)
            read >> points2[i][0] >> points2[i][1];

        cout << "Print points" << endl;
        for (int i = 0; i < size; i++)
            cout << "X: " << points2[i][0] << " Y: " << points2[i][1] << endl;

        double value;
        cout << "Enter the X value for which you are looking for the Y value." << endl;
        cin >> value;

        cout << "For the given x= " << value << " the y value is: " << findNewton(size, value, points2) << endl;

        // Zwolnienie zaalokowanej pamiêci
        for (int i = 0; i < size; i++) {
            delete[] points2[i];
        }
        delete[] points2;
    }
    else
        cout << "Nie udalo sie otworzyc pliku" << endl;

    read.close();

    return 0;
}
