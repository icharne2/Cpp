#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

//Funkcja dla kt�rej b�dzie liczona ca�ka
double function(double x) {
	return exp(3 * x);
}

double RectangularlMethod(double x_s, double x_e, double numberOfRectangles) {
	double dx = (x_e - x_s) / numberOfRectangles;
	double sum = 0., x_i = x_s;

	for (int i = 0; i < numberOfRectangles; i++) {
		x_i += dx;
		sum += function(x_i);
	}

	return dx * sum;
}

double TrapezoidalMethod(double x_s, double x_e, double numberOfTrapezoids) {
	double dx = (x_e - x_s) / numberOfTrapezoids;
	double sum = (function(x_s) + function(x_e)) / 2; // Dodaj warto�ci funkcji na ko�cach przedzia�u
	double x_i = x_s + dx; // Rozpocznij od pierwszego trapezu

	for (int i = 1; i < numberOfTrapezoids; i++) {
		sum += function(x_i);
		x_i += dx;
	}

	return dx * sum;
}

double SimpsonMethod(double x_s, double x_e, double number) {
	double dx = (x_e - x_s) / number; // szeroko�� przedzia�u
	double I = 0.0, a, b, midpoint;

	for (int i = 0; i < number; i++) {
		a = x_s + i * dx; // pocz�tek podprzedzia�u
		b = x_s + (i + 1) * dx; // koniec podprzedzia�u
		midpoint = (a + b) / 2.; // �rodek podprzedzia�u

		// Obliczenie warto�ci funkcji w punktach a, b i �rodku podprzedzia�u
		double fa = function(a);
		double fb = function(b);
		double fmid = function(midpoint);

		// Obliczenie sumy dla tego podprzedzia�u i dodanie do ca�kowitej sumy
		I += dx*(fa + 4 * fmid + fb)/6.;	//6 poniewaz dx to 2*szeroko�� h
	}

	return I;
}

double MCMethod(double x_s, double x_e, double number) {
	srand(time(nullptr));
	double sum = 0.0, dx = x_e - x_s;

	for (int i = 0; i < number; i++) {
		double u = (double)rand() / RAND_MAX; // Losowa liczba zmiennoprzecinkowa z przedzia�u [0, 1)
		double x = x_s + u * dx; // Losowy punkt w przedziale [x_s, x_e]
		sum += function(x); 
	}

	sum *= dx / number;

	return sum;
}


int main() {
	//Przybli�anie ca�ki oznaczonej
	//Metoda prostok�t�w, trapez�w, Simpson'a, MC
	double x_s, x_e, number;

	cout << "Give the interval of the integral.\nStart:" << endl;
	cin >> x_s;
	cout << "End:" << endl;
	cin >> x_e;

	if (x_s < x_e) {
		cout << "Enter the number: " << endl;
		cin >> number;

		cout << "RectangularlMethod P = " << RectangularlMethod(x_s, x_e, number) << endl;
		cout << "TrapezoidalMethod P = " << TrapezoidalMethod(x_s, x_e, number) << endl;
		cout << "SimpsonMethod P = " << SimpsonMethod(x_s, x_e, number) << endl;
		cout << "MCMethod P = " << MCMethod(x_s, x_e, number) << endl;
	}
	else {
		cout << "Invalid data :<" << endl;
	}

	system("PAUSE");
	return 0;
}