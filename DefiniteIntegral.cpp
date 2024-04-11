#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

//Funkcja dla której bêdzie liczona ca³ka
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
	double sum = (function(x_s) + function(x_e)) / 2; // Dodaj wartoœci funkcji na koñcach przedzia³u
	double x_i = x_s + dx; // Rozpocznij od pierwszego trapezu

	for (int i = 1; i < numberOfTrapezoids; i++) {
		sum += function(x_i);
		x_i += dx;
	}

	return dx * sum;
}

double SimpsonMethod(double x_s, double x_e, double number) {
	double dx = (x_e - x_s) / number; // szerokoœæ przedzia³u
	double I = 0.0, a, b, midpoint;

	for (int i = 0; i < number; i++) {
		a = x_s + i * dx; // pocz¹tek podprzedzia³u
		b = x_s + (i + 1) * dx; // koniec podprzedzia³u
		midpoint = (a + b) / 2.; // œrodek podprzedzia³u

		// Obliczenie wartoœci funkcji w punktach a, b i œrodku podprzedzia³u
		double fa = function(a);
		double fb = function(b);
		double fmid = function(midpoint);

		// Obliczenie sumy dla tego podprzedzia³u i dodanie do ca³kowitej sumy
		I += dx*(fa + 4 * fmid + fb)/6.;	//6 poniewaz dx to 2*szerokoœæ h
	}

	return I;
}

double MCMethod(double x_s, double x_e, double number) {
	srand(time(nullptr));
	double sum = 0.0, dx = x_e - x_s;

	for (int i = 0; i < number; i++) {
		double u = (double)rand() / RAND_MAX; // Losowa liczba zmiennoprzecinkowa z przedzia³u [0, 1)
		double x = x_s + u * dx; // Losowy punkt w przedziale [x_s, x_e]
		sum += function(x); 
	}

	sum *= dx / number;

	return sum;
}


int main() {
	//Przybli¿anie ca³ki oznaczonej
	//Metoda prostok¹tów, trapezów, Simpson'a, MC
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