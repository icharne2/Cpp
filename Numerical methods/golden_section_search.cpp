#include <iostream>
#include <cmath>

using namespace std;

const double PHI = 0.61803398875;  // Golden ratio approximation
const double epsilon = 1e-5; // Desired precision

// Function to minimize
double functionToMinimize(double x) {
    return (x - 2) * (x - 2);
};

double goldenSectionSearch(double a, double b) {
    double x1 = b - PHI * (b - a);
    double x2 = a + PHI * (b - a);
    double f1 = functionToMinimize(x1);
    double f2 = functionToMinimize(x2);

    while ((b - a) > epsilon) {
        if (f1 > f2) {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + PHI * (b - a);
            f2 = functionToMinimize(x2);
        }
        else {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - PHI * (b - a);
            f1 = functionToMinimize(x1);
        }
    }
    return (a + b) / 2;

}

int main() {
    double a = 0; // Lower bound of search interval
    double b = 4; // Upper bound of search interval

    cout << "The minimum value is located at x = " << goldenSectionSearch(a, b) << endl;

    system("PAUSE");
    return 0;
}
