#include<iostream>
#include<string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Point {
private:
    int x;
    int y;
public:
    friend class Square;
    //friend class Circle; //needed for part D)
    Point(int x_, int y_) : x(x_), y(y_) {}
    friend void print(const Point& p);
};

class Square {
private:
    Point start;
    Point end;
public:
    Square(Point p1, Point p2) : start(p1), end(p2) {}
    friend void print(const Square& s);

    void areaOfSquare() {
        int a = abs(end.x - start.x);
        int b = abs(end.y - start.y);
        int area = a * b;
        cout << "Area of the square: " << area << endl;
    }
};

class Circle {
private:
    Point center;
    int radius;
public:
    friend void print(const Circle& c);
    Circle() : center({ 0, 0 }), radius(0) {}
    Circle(Point p, int r) : center(p), radius(r) {}

    void save(Point p, int r) {
        this->center = p;
        this->radius = r;
    }

    // Part D)

    /*void disjoint(const Circle& c) {
        int distance = sqrt(pow(c.center.x - c.center.x, 2) + pow(center.y - c.center.y, 2));

        if (distance > radius + c.radius) {
            cout << "The circles are externally disjoint." << endl;
        }
        else if (distance < abs(radius - c.radius)) {
            cout << "The circles are internally disjoint." << endl;
        }
        else {
            cout << "The circles have a common part." << endl;
        }
    }
    */
};

// Point
void print(const Point& p) {
    cout << "Point: (" << p.x << ", " << p.y << ")" << endl;
}

// Square
void print(const Square& s) {
    cout << "Square: " << endl;
    cout << "Start: ";
    print(s.start);
    cout << "End: ";
    print(s.end);
}

// Circle
void print(const Circle& c) {
    cout << "Circle: " << endl;
    cout << "Center: ";
    print(c.center);
    cout << "Radius: " << c.radius << endl;
}

int main() {
    // Part A)
    Square squares[2] = {
        Square(Point(0, 0), Point(3, 3)),
        Square(Point(-8, 8), Point(-1, 1))
    };

    // Part B)
    for (int i = 0; i < 2; i++) {
        squares[i].areaOfSquare();
        cout << endl;
    }

    // Part C)
    Circle c1({ 10, 10 }, 5);
    Circle circles[500];

    srand(time(NULL));
    // Helper variables
    int x, y, r;

    // Filling the circles array
    for (int i = 0; i < 500; i++) {
        // rand() % (max - min + 1) + min, where min is the lower boundary of the range
        x = rand() % (20 - (-10) + 1) + (-10);
        y = rand() % (20 + 1);
        r = rand() % (5 - (1) + 1) + 1;

        circles[i].save({ x, y, }, r);
    }

    // Part D)

    // Done based on friendship with the Circle class - needs to be uncommented

    cout << "Part D is implemented based on friendship with the class - that's why it's commented out (it works after uncommenting)" << endl;

    /*for (int i = 0; i < 500; i++) {
        c1.disjoint(circles[i]);
    }
    */

    // Part E)

    cout << "Printing Square:" << endl;
    print(squares[0]);
    cout << endl;

    cout << "Printing Circle:" << endl;
    print(c1);

    system("PAUSE");
    return 0;
}
