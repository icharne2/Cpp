#include<iostream>
#include<string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction() {}
    Fraction(int n, int d) : numerator(n), denominator(d) {}
    Fraction(int number) : numerator(number), denominator(1) {}

    void print() {
        cout << numerator << "/" << denominator << endl;
    }

    int getNumerator() {
        return numerator;
    }

    int getDenominator() {
        return denominator;
    }

    operator double() {
        return (double)numerator / static_cast<double>(denominator);
    }

    Fraction reduceFraction() {
        int a = numerator, b = denominator, temp;

        while (b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }
        numerator /= a;
        denominator /= a;
        return *this;
    }

};

Fraction add(Fraction f1, Fraction f2) {
    Fraction result(f1.getNumerator() * f2.getDenominator() + f2.getNumerator() * f1.getDenominator(), f1.getDenominator() * f2.getDenominator());
    return result;
}

double squareOfNumber(double number) {
    return number * number;
}

void pointF(int n) {
    Fraction* arr = new Fraction[n];

    cout << "Generated fractions:" << endl;
    for (int i = 0; i < n; i++) {
        int numerator = rand() % 2001 - 1000;
        int denominator = rand() % 2001 - 1000;
        while (denominator == 0) { // Denominator cannot be zero
            denominator = rand() % 2001 - 1000;
        }

        Fraction newFraction(numerator, denominator);
        arr[i] = newFraction;

        newFraction.print();
    }

    cout << "The largest fraction: ";
    Fraction max = arr[0];

    for (int i = 1; i < n; i++) {
        if (static_cast<double>(arr[i]) > static_cast<double>(max)) {
            max = arr[i];
        }
    }
    max.print();
}

int main() {
    srand(time(NULL));

    // Part A)
    cout << "Part A)" << endl;

    Fraction array[3] = { Fraction(1, 2), Fraction(5, 8), Fraction(7, 9) };

    for (int i = 0; i < 3; i++) {
        array[i].print();
    }

    // Part B)
    cout << "Part B)" << endl;

    Fraction result = add(array[0], array[1]);

    cout << "Sum of the first two fractions: " << endl;

    result.print();

    // Part C)
    cout << "Part C)" << endl;

    result = add(array[0], 7);

    cout << "Sum of 1/2 and 7: " << endl;

    result.print();

    // Part D)
    cout << "Part D)" << endl;

    double square = squareOfNumber(array[2]);
    cout << "Square of the number:\n" << square << endl;

    // Part E)
    cout << "Part E)" << endl;

    Fraction f(88, 22);
    cout << "Fraction ";
    f.print();
    cout << "after reduction is: ";
    f.reduceFraction();
    f.print();

    // Part F)
    cout << "Part F)" << endl;

    int n;
    cout << "Enter the number of elements (N):" << endl;
    cin >> n;

    pointF(n);

    system("PAUSE");
    return 0;
}
