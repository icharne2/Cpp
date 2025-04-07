#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Differential equation 
double differential_equation(double x, double y) {
    return sin(x);
}

// Analytical solution 
double analytical_solution(double x) {
    return -cos(x) + cos(0);  // y(x) = -cos(x) + cos(0)
}

// RK4's method
double RK4_solution(double initial_x, double final_x, double initial_y, double step) {
    int num_steps = (final_x - initial_x) / step;
    double x = initial_x;
    double y = initial_y;

    cout << "RK4's method:" << endl;

    for (int i = 0; i < num_steps; i++) {
        double k1 = step * differential_equation(x, y);
        double k2 = step * differential_equation(x + 0.5 * step, y + 0.5 * k1);
        double k3 = step * differential_equation(x + 0.5 * step, y + 0.5 * k2);
        double k4 = step * differential_equation(x + step, y + k3);

        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        cout << "\tY_" << i << " solution: " << y << endl;
        x += step;
    }

    return y;
}

// Euler's method
double euler_solution(double initial_x, double final_x, double initial_y, double step) {
    int num_steps = (final_x - initial_x) / step;
    double x = initial_x;
    double y = initial_y;

    cout << "Euler's method:" << endl;

    for (int i = 0; i < num_steps; i++) {
        y += step * differential_equation(x, y);
        cout << "\tY_" << i << " solution: " << y << endl;
        x += step;
    }

    return y;
}

// Heun's method
double heun_solution(double initial_x, double final_x, double initial_y, double step) {
    int num_steps = (final_x - initial_x) / step;
    double x = initial_x;
    double y = initial_y;

    cout << "Heun's method:" << endl;

    for (int i = 0; i < num_steps; i++) {
        double k1 = differential_equation(x, y);
        double k2 = differential_equation(x + step, y + step * k1);
        y += step / 2.0 * (k1 + k2);
        cout << "\tY_" << i << " solution: " << y << endl;
        x += step;
    }

    return y;
}

int main() {
    double initial_x = 0;
    double final_x = 3.141592653589793238;
    double initial_y = 0;
    double step = 0.1;

    cout << "Euler's method: " << euler_solution(initial_x, final_x, initial_y, step) << endl;
    cout << "Heun's method: " << heun_solution(initial_x, final_x, initial_y, step) << endl;
    cout << "RK4's method: " << RK4_solution(initial_x, final_x, initial_y, step) << endl;
    cout << "Analytical solution result: " << analytical_solution(final_x) << endl;

    system("PAUSE");
    return 0;
}
