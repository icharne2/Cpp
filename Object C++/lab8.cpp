#include<iostream>
#include<math.h>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

class Vector {
private:
    int x;
    int y;
public:
    Vector() {};
    Vector(int x_v, int y_v) : x(x_v), y(y_v) {}

    // Printing
    friend ostream& operator<<(ostream& stm, const Vector& v)
    {
        stm << "[" << v.x << ", " << v.y << "]";
        return stm;
    }

    // Adding vectors
    Vector operator+(const Vector& other) const
    {
        Vector result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        return result;
    }

    // Subtracting vectors
    Vector operator-(const Vector& other) const
    {
        Vector result;
        result.x = this->x - other.x;
        result.y = this->y - other.y;
        return result;
    }

    // Multiplying vectors
    int operator*(const Vector& other) const
    {
        return this->x * other.x + this->y * other.y;
    }

    // Length of vector
    double length() const {
        return sqrt(x * x + y * y);
    }

    // Get values
    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }
};

// Check which element is longer:
bool compareByLength(Vector& a, Vector& b)
{
    return a.length() < b.length();
}

// Bubble sort for an array of n elements
void bubbleSort(Vector arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compareByLength(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Calculate the distance between vectors
double distance(Vector& v1, Vector& v2) {
    Vector res = v1 - v2;
    return sqrt(res.getX() * res.getX() + res.getY() * res.getY());
}

// Finding the closest vector
Vector findClosestVector(Vector arr[], int size, Vector& target) {
    double closeDistance = distance(arr[0], target);
    int closestIndex = 0;

    for (int i = 1; i < size; ++i) {
        double currentDistance = distance(arr[i], target);
        if (currentDistance < closeDistance) {
            closeDistance = currentDistance;
            closestIndex = i;
        }
    }
    return arr[closestIndex];
}

int main() {
    srand(time(NULL));

    // Part A)
    cout << "Part A)" << endl;
    Vector v1(3, 5);
    Vector v2(-2, 7);

    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    // Part B)
    cout << "Part B)" << endl;
    cout << "v1 + v2 = " << v1 + v2 << endl;

    // Part C)
    cout << "Part C)" << endl;
    cout << "v1 * v2 = " << v1 * v2 << endl;

    // Part D)
    cout << "Part D)" << endl;
    Vector arr[20];

    for (int x, y, i = 0; i < 20; i++) {
        x = rand() % 31 - 15;
        y = rand() % 31 - 15;
        arr[i] = Vector(x, y);
    }

    bubbleSort(arr, 20);

    for (int i = 0; i < 20; i++) {
        cout << "Vector no. " << i + 1 << ": " << arr[i] << ", with length: " << arr[i].length() << endl;
    }

    // Part E)
    cout << "Part E)" << endl;

    Vector closestVector = findClosestVector(arr, 20, v1);

    cout << "The closest vector to: " << v1 << " is: " << closestVector << endl;
    cout << "The length of this vector is: " << closestVector.length() << endl;

    system("PAUSE");
    return 0;
}
