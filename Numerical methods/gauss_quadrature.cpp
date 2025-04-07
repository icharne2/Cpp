#include<iostream>
#include<cstdlib>
#include <iostream>
#include <fstream>
#include<cmath>

using namespace std;

//Funkcja obliczaj¹ca ca³ke podwujn¹ dla ustalonych wag i wez³ów (punktów)
double gaussQuadrature(double (*points)[4]) {
    double surface = 0.0, dxdKSI, dydKSI, dxdETA, dydETA;
    double scales[2] = { 1, 1 };    //Przyjete wagi
    double nodes[2] = { -0.5773502692, 0.5773502692 };
    double derivative_ksi[2][4], derivative_eta[2][4], FUN_DETJ[2][2];

    // Obliczenie pochodnych cz¹stkowych
    for (int i = 0; i < 2; i++) {
        // Obliczanie pochodnych w kierunku ksi (x)
        derivative_ksi[i][0] = -0.25 * (1.0 - nodes[i]);
        derivative_ksi[i][1] = 0.25 * (1.0 - nodes[i]);
        derivative_ksi[i][2] = 0.25 * (1.0 + nodes[i]);
        derivative_ksi[i][3] = -0.25 * (1.0 + nodes[i]);

        //Obliczanie pochodnych w kierunku eta (y)
        derivative_eta[i][0] = -0.25 * (1.0 - nodes[i]);
        derivative_eta[i][1] = -0.25 * (1.0 + nodes[i]);
        derivative_eta[i][2] = 0.25 * (1.0 + nodes[i]);
        derivative_eta[i][3] = 0.25 * (1.0 - nodes[i]);
    }

    // Obliczanie powierzchni (ca³ki)
    for (int i = 0; i < 2; i++) {
        // Obliczenie pochodnych cz¹stkowych w punktach kwadratury
        dxdKSI = derivative_ksi[i][0] * points[0][0] + derivative_ksi[i][1] * points[1][0] + derivative_ksi[i][2] * points[2][0] + derivative_ksi[i][3] * points[3][0];
        dydKSI = derivative_ksi[i][0] * points[0][1] + derivative_ksi[i][1] * points[1][1] + derivative_ksi[i][2] * points[2][1] + derivative_ksi[i][3] * points[3][1];

        dxdETA = derivative_eta[i][0] * points[0][0] + derivative_eta[i][1] * points[1][0] + derivative_eta[i][2] * points[2][0] + derivative_eta[i][3] * points[3][0];
        dydETA = derivative_eta[i][0] * points[0][1] + derivative_eta[i][1] * points[1][1] + derivative_eta[i][2] * points[2][1] + derivative_eta[i][3] * points[3][1];

        // Obliczenie wartoœci wyznacznika Jacobiego dla ka¿dego punktu kwadratury
        FUN_DETJ[i][0] = dxdKSI * dydETA - dydKSI * dxdETA;
        FUN_DETJ[i][1] = dxdKSI * dydETA - dydKSI * dxdETA;
    }

    //Sumowanie wartoœci bezwzglêdnych wyznaczników Jacobiego, skalowanie i dodanie do powierzchni
    for (int i = 0; i < 2; i++) {
        surface += fabs(FUN_DETJ[i][0]) * scales[0] * scales[1];
        surface += fabs(FUN_DETJ[i][1]) * scales[0] * scales[1];
    }
    return surface;
}


int main() {
	//Ca³ki podwójne - kwadratura Gaussa 2D - 4 punktowe
    //Odczyt danych punktów dla których szukamy funkcji
    fstream read("MN6.txt");
    double points[4][4]; // Tablica punktów x, y

    if (read.is_open()) {
        // Odczytanie danych do tablicy dwuwymiarowej i wypisanie
        cout << "Points:" << endl;

        for (int i = 0; i < 4; i++) {
            read >> points[i][0] >> points[i][1];
            cout << "P=(" << points[i][0] << "," << points[i][1] << ")" << endl;
        }
        // Obliczanie powierzchni - ca³ki
        cout << "Calculated area: " << gaussQuadrature(points) << endl;

    }
    else
        cout << "Failed to open the file :<" << endl;

    read.close();

	system("PAUSE");
	return 0;
}