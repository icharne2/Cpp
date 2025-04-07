#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Funkcja do wczytywania danych z pliku
void readData(const string& fileName, vector<vector<double>>& A, vector<double>& b) {
    ifstream plik(fileName);

    if (!plik.is_open()) {
        cout << "Can't open this file :<" << endl;
        return;
    }

    int size;
    plik >> size;

    A.resize(size, vector<double>(size));
    b.resize(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            plik >> A[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        plik >> b[i];
    }

    plik.close();
}

// Funkcja do eliminacji Gaussa bez pivotowania
vector<double> gaussElimination(vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();

    // Postêpowanie proste (eliminacja w przód)
    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];

            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // Postêpowanie odwrotne (eliminacja wsteczna)
    vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];

        for (int j = i + 1; j < n; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

// Funkcja do eliminacji Gaussa z pivotowaniem wierszowym
vector<double> rowPivotGauss(vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();

    // Pivotowanie wierszowe
    for (int k = 0; k < n; ++k) {
        // Znajdowanie maksimum w kolumnie k zaczynaj¹c od wiersza k
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (abs(A[i][k]) > abs(A[maxRow][k])) {
                maxRow = i;
            }
        }

        // Zamiana wierszy
        swap(A[k], A[maxRow]);
        swap(b[k], b[maxRow]);

        // Eliminacja Gaussa
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; ++j) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    // Postêpowanie odwrotne (eliminacja wsteczna)
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];

        for (int j = i + 1; j < n; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

// Funkcja do eliminacji Gaussa z pivotowaniem kolumnowym
vector<double> columnPivotGauss(vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();

    // Tablica przechowuj¹ca kolejnoœæ kolumn
    vector<int> order(n);
    for (int i = 0; i < n; ++i)
        order[i] = i;

    // Pivotowanie kolumnowe
    for (int k = 0; k < n; ++k) {
        // Znajdowanie maksimum w kolumnie k zaczynaj¹c od wiersza k
        int maxCol = k;
        for (int j = k + 1; j < n; ++j) {
            if (abs(A[k][j]) > abs(A[k][maxCol])) {
                maxCol = j;
            }
        }

        // Zamiana kolumn
        for (int i = 0; i < n; ++i) {
            swap(A[i][k], A[i][maxCol]);
        }
        swap(order[k], order[maxCol]);

        // Eliminacja Gaussa
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; ++j) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    // Postêpowanie odwrotne (eliminacja wsteczna)
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];

        for (int j = i + 1; j < n; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    // Przywracanie oryginalnej kolejnoœci kolumn
    vector<double> finalResult(n);
    for (int i = 0; i < n; ++i) {
        finalResult[order[i]] = x[i];
    }

    return finalResult;
}

// Funkcja do wyœwietlania macierzy i wektora
void printData(const vector<vector<double>>& A, const vector<double>& b) {
    cout << "Matrix A:" << endl;
    for (const auto& row : A) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    cout << "\nVector b:" << endl;
    for (const auto& elem : b) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    string fileName = "data3.txt";
    vector<vector<double>> A;
    vector<double> b;

    readData(fileName, A, b);

    // Wyœwietlenie macierzy i wektora
    printData(A, b);

    // Kopiowanie macierzy i wektora do ponownego u¿ycia
    vector<vector<double>> A_copy = A;
    vector<double> b_copy = b;

    // Pomiar czasu dla eliminacji Gaussa bez pivotowania
    auto start = high_resolution_clock::now();
    vector<double> resultNoPivot = gaussElimination(A_copy, b_copy);
    auto stop = high_resolution_clock::now();
    auto durationNoPivot = duration_cast<microseconds>(stop - start);

    // Wyœwietlenie wyniku
    cout << "\nResults without pivoting: - " << durationNoPivot.count() << " microseconds." << endl;
    for (int i = 0; i < resultNoPivot.size(); ++i) {
        cout << "x_" << i << " = " << resultNoPivot[i] << " ";
    }
    cout << endl;

    // Ponowne wczytanie danych
    readData(fileName, A, b);

    // Pomiar czasu dla eliminacji Gaussa z pivotowaniem wierszowym
    start = high_resolution_clock::now();
    vector<double> resultRowPivot = rowPivotGauss(A, b);
    stop = high_resolution_clock::now();
    auto durationRowPivot = duration_cast<microseconds>(stop - start);

    // Wyœwietlenie wyniku
    cout << "\nResults with row pivoting: - " << durationRowPivot.count() << " microseconds." << endl;
    for (int i = 0; i < resultRowPivot.size(); ++i) {
        cout << "x_" << i << " = " << resultRowPivot[i] << " ";
    }
    cout << endl;

    // Ponowne wczytanie danych
    readData(fileName, A, b);

    // Pomiar czasu dla eliminacji Gaussa z pivotowaniem kolumnowym
    start = high_resolution_clock::now();
    vector<double> resultColPivot = columnPivotGauss(A, b);
    stop = high_resolution_clock::now();
    auto durationColPivot = duration_cast<microseconds>(stop - start);

    // Wyœwietlenie wyniku
    cout << "\nResults with column pivoting: - " << durationColPivot.count() << " microseconds." << endl;
    for (int i = 0; i < resultColPivot.size(); ++i) {
        cout << "x_" << i << " = " << resultColPivot[i] << " ";
    }
    cout << endl;

    return 0;
}