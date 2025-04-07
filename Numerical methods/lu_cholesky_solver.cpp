#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void LU_method_decomposition(double** A, double** L, double** U, int n) {
    for (int i = 0; i < n; i++) {
        L[i] = new double[n];
        U[i] = new double[n];

        for (int j = 0; j < n; j++) {
            if (i == j)
                L[i][j] = 1;
            else {
                L[i][j] = 0;
                U[i][j] = 0;
            }
        }
    }

    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += L[i][k] * U[k][j];
                U[i][j] = A[i][j] - sum;
            } else {
                sum = 0;
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * U[k][j];
                L[i][j] = (A[i][j] - sum) / U[j][j];
            }
        }
    }
}

double* solve_LU_method(double** A, double* B, int n) {
    //Dkleracja nowych macierzy U i L
    double** L = new double*[n];
    double** U = new double*[n];

    LU_method_decomposition(A, L, U, n);

    double sum = 0.0;
    double* Y = new double[n];

    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * Y[j];
        Y[i] = (B[i] - sum) / L[i][i];
    }

    double* X = new double[n];
    for (int i = n - 1; i >= 0; i--) {
        sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * X[j];
        X[i] = (Y[i] - sum) / U[i][i];
    }

    for (int i = 0; i < n; i++) {
        delete[] L[i];
        delete[] U[i];
    }
    delete[] L;
    delete[] U;
    delete[] Y;
    return X;
}

void readFile(string fileName, int& n, double**& A, double*& B) {
    ifstream file(fileName);

    if (!file) {
        cerr << "Cannot open this file :<." << endl;
        return;
    }

    file >> n;

    A = new double* [n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        for (int j = 0; j < n; j++)
            file >> A[i][j];
    }

    B = new double[n];
    for (int i = 0; i < n; i++)
        file >> B[i];

    file.close();
}

void Cholesky_method_decomposition(double** A, double** L, int n) {
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            sum = 0;
            if (j == i) { // Wartoœci na przek¹tnych
                for (int k = 0; k < j; k++)
                    sum += L[j][k] * L[j][k];
                L[j][j] = sqrt(A[j][j] - sum);
            }
            else { // Pozosta³e wartoœci w macierzy
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

double* solve_Cholesky_method(double** A, double* B, int n) {
    double sum=0.0;
    double** L = new double* [n];

    for (int i = 0; i < n; ++i)
        L[i] = new double[n];
    Cholesky_method_decomposition(A, L, n); // Zamiana macierzy A na macierz L

    double* Y = new double[n];
    for (int i = 0; i < n; i++) { // Wyliczanie wektora Y
        sum = 0;
        for (int j = 0; j < i; ++j)
            sum += L[i][j] * Y[j];
        Y[i] = (B[i] - sum) / L[i][i];
    }

    double* X = new double[n]; // Wyliczanie wektora X
    for (int i = n - 1; i >= 0; i--) {
        sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += L[j][i] * X[j];
        X[i] = (Y[i] - sum) / L[i][i];
    }

    for (int i = 0; i < n; ++i)
        delete[] L[i];
    delete[] L;
    delete[] Y;
    return X;
}

int main() {
    int n;
    double** A, **A2;
    double* B, *B2;

    readFile("macierz.txt", n, A, B); 

    //Kopie macierzy
    A2 = new double* [n];
    for (int i = 0; i < n; i++) {
        A2[i] = new double[n];
        for (int j = 0; j < n; j++)
            A2[i][j] = A[i][j];
    }

    B2 = new double[n];
    for (int i = 0; i < n; i++)
        B2[i] = B[i];

    //Wywolanie funkcji
    double* X_LU = solve_LU_method(A, B, n);

    double* X_Cholesky = solve_Cholesky_method(A2, B2, n);

    cout << "Solve - method LU:" << endl;
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << setw(10) << X_LU[i] << endl;

    cout << "Solve - method Choleskiego:" << endl;
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << setw(10) << X_Cholesky[i] << endl;

    //Czyszczenie pamiêci
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;
    delete[] B;
    delete[] X_LU;
    delete[] X_Cholesky;

    return 0;
}
