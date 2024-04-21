#include<iostream>
#include<cmath>

using namespace std;

// Zmienna globalna dla tolerancji
const double tolerance = 1e-6;

// Definicja funkcji, dla której szukamy pierwiastka
double function(double x) {
    return sin(x) + cos(x); // Przyk³adowa funkcja
}

// Pochodna funkcji dla powy¿szej funkcji
double derivative(double x) {
    return cos(x) - sin(x);
}

// Metoda bisekcji
void bistection(double start, double end) {
    double x = 0.0;   // Zmienna przechowuj¹ca start+end/2
    int i = 0; // Zmienna pomocnicza do iteracji w pêtli

    // Sprawdzenie warunku
    if (function(start) * function(end) > 0) {
        cout << "No sign change at the ends of the interval - bisection." << endl;
    }
    else {
        do {
            x = (start + end) / 2;
            if (function(x) == 0.0) {
                break;
            }
            else if (function(x) * function(start) < 0) {
                end = x;
            }
            else {
                start = x;
            }
            i++;
        } while (fabs(function(x)) > tolerance && (i < 1000));
    }
    cout << "Found root - bisection: " << x << endl;
}

// Metoda Newtona-Raphsona
double newtonRaphson(double x_0) {
    int i = 0; // Zmienna pomocnicza do iteracji w pêtli
    double xi = x_0;
    double f_xn = function(x_0);

    while (fabs(f_xn) > tolerance && i < 10000) {
        double f_prime_xi = derivative(xi);

        if (f_prime_xi == 0) {
            return 0;
        }

        double xn_next = xi - f_xn / f_prime_xi;

        if (fabs(xn_next - xi) <= tolerance) {
            return xn_next;
        }
        xi = xn_next;
        f_xn = function(xi);
        i++;
    }

    if (fabs(f_xn) <= tolerance) {
        return xi;
    }
    else {
        return 0;
    }
}

int main() {
    // Metody szukania pierwiastków dla podanej funkcji
    // Metoda bisekcji
    double a, b;    // Deklaracja zmiennych a,b s³u¿¹cych do okreœlenia przedzia³u

    cout << "Enter the interval [a, b]: " << endl;
    cin >> a >> b;

    bistection(a, b);

    // Metoda Newtona-Raphsona
    double x_0 = 2.0;    // Ustalenie pocz¹tkowego przybli¿enia pierwiastka na podstawie wykresu funkcji
    double result = newtonRaphson(x_0);

    if (result)
        cout << "Found root - Newton-Raphson: " << result << endl;
    else
        cout << "Root not found - Newton-Raphson." << endl;

    system("PAUSE");
    return 0;
}
