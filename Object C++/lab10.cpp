#include <iostream>

using namespace std;

template <typename T, typename R>
class Calculator {
private:
    T x;
    R y;

public:
    Calculator(T x_, R y_) : x(x_), y(y_) {}

    T add() { return x + y; }   // Addition

    T subtract() { return x - y; }   // Subtraction

    T multiply() { return x * y; } // Multiplication

    T divide() {    // Division with exception to prevent division by zero
        if (y != 0) {
            return x / y;
        }
        else {
            throw exception("Cannot divide by 0");
        }
    }
};

int main() {
    // Task 1,2
    try {
        // a)
        Calculator<int, int> intCalculator(3, 8);

        cout << "3 + 8 = " << intCalculator.add() << endl;
        cout << "3 - 8 = " << intCalculator.subtract() << endl;
        cout << "3 * 8 = " << intCalculator.multiply() << endl;
        cout << "3 / 8 = " << intCalculator.divide() << endl;

        // b)
        Calculator<float, float> floatCalculator(2.53f, 2.99f);

        cout << "2.53 + 2.99 = " << floatCalculator.add() << endl;
        cout << "2.53 - 2.99 = " << floatCalculator.subtract() << endl;
        cout << "2.53 * 2.99 = " << floatCalculator.multiply() << endl;
        cout << "2.53 / 2.99 = " << floatCalculator.divide() << endl;

        // c)
        Calculator<double, unsigned int> doubleCalculator(5.22, 7);

        cout << "5.22 + 7 = " << doubleCalculator.add() << endl;
        cout << "5.22 - 7 = " << doubleCalculator.subtract() << endl;
        cout << "5.22 * 7 = " << doubleCalculator.multiply() << endl;
        cout << "5.22 / 7 = " << doubleCalculator.divide() << endl;
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
